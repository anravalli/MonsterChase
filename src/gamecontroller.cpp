/*
 *	Monster Chase: a testing playground for behaviors trees
 *
 *	Copyright 2021 Andrea Ravalli <anravalli @ gmail.com>
 *
 *	This file is part of Monster Chase.
 *
 *	Monster Chase is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.

 *	Monster Chase is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.

 *	You should have received a copy of the GNU General Public License
 *	along with Monster Chase.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "gamecontroller.h"
#include "gameviews.h"
#include "gameworld.h"
#include "gameconfig.h"
#include "arena.h"
#include "player.h"
#include "monster.h"

#include <ui_framework/uipagemenu.h>

#define FRAMERATE 50
#define UPDATE_PERIOD 1000/FRAMERATE

const char *match_type_tostr(MatchType mt)
{
	static const char *mt_strings[] = {"no match", "hunter", "survivor", "the dark hunt", "alone in the dark"};
	return mt_strings[mt];
}


GameController::GameController(UiPageController *parent):
    UiPageController(parent), is_paused(true)
{
    initPageView<GamePage>();

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(gameStep()));

    pause_menu = create_pause_menu();
}

//TODO: removeFromPage() needed
void GameController::initMatch(){
	QString map = ":/resources/map.txt";
	GameWorld::instance().initLevel(map);

	Arena* arena = GameWorld::instance().getArena();
	arena->addToPage(page_view);
	connect(arena,SIGNAL(build_complete()),this,SLOT(start()));

	GameWorld::instance().getPlayer()->addToPage(page_view);
	for(auto m: GameWorld::instance().getMonsters())
		m->addToPage(page_view);
	pause_menu->addToPage(page_view);
}

void GameController::show(){
	initMatch();
    UiPageController::show();
    GameWorld::instance().getArena()->show();
}

void GameController::start(){
    addPlayTime(); //test
    qDebug("Starting match: %s",match_type_tostr(match_type));
    switch(match_type)
    {
    case mt_hunter:
    case mt_survivor:
    case mt_the_dark_hunt:
    case mt_alone_in_the_dark:
		GameWorld::instance().start();
		timer->start(UPDATE_PERIOD);
		is_paused = false;
		break;
    default:
    	break;
    }
}

//for game states: start here
void GameController::exit(){
	qDebug("GameController::exit()");
	GameWorld::instance().deInitLevel();
	UiPageController::exit();
}


UiPageMenu *GameController::create_pause_menu()
{
	vector<QString> popup_model = {"yes", "not"};
	vector<function<void()>> popup_actions;
	popup_actions.push_back([this]{this->exit();});
	popup_actions.push_back([this]{this->togglePause();});

	auto *popup_view = new UiPagePopupWidget_qt(QString("Do you want to leave the match?"),
			new UiPageMenuWidget_qt(&popup_model));

	auto popup_menu = new UiPageMenu(popup_actions, popup_view, 1);
	popup_menu->setPos(GameConfig::playground_width/2, GameConfig::playground_height/2);
	popup_menu->hide();

	return popup_menu;
}

void GameController::togglePause(){
    qDebug("GameController::togglePause()");
    qDebug("is_paused %d", is_paused);
    if(is_paused){
    	timer->start();
    	is_paused = false;
    	current_menu = nullptr;
    	pause_menu->hide();
    }
    else{
    	timer->stop();
    	is_paused = true;
    	current_menu = pause_menu;
    	pause_menu->show();
    }
}

//destructor currently unused
GameController::~GameController()
{
	GameWorld::instance().deInitLevel();
	delete page_view;
    delete ptime;
    delete timer;
    delete pause_menu;
    if(match_end_menu)
    	delete match_end_menu;
}

void GameController::addPlayTime(){
    ptime = new PlayTime(FRAMERATE);
    ptime->setPos(-GameConfig::playground_border_width/2,
                  -GameConfig::playground_border_height*0.6);
    page_view->addItem(ptime);
}

class MatchEndPopup: public UiPageMenu
{
public:
	MatchEndPopup(vector<function<void()>> actions, UiPageAbstractMenuWidget *view, int start_index):
		UiPageMenu(actions, view, start_index){}

	virtual bool handleKey(int key, bool released) override final {
	    bool ret = false;
	    switch(key){
	    case Qt::Key_Enter:
	    case Qt::Key_Return:
	        run_item_action(released);
	        ret = true;
	        break;
	    default:
	        break;
	    }
	    return ret;
	}
};

UiPageMenu *GameController::create_match_ended_popup(int score, int energy, int play_time,
		int final_score, QString message)
{
	//temporary using a standard popup menu
	QString s_score = QString::asprintf("score: %d", score);
	QString s_energy = QString::asprintf("energy: %d", energy);
	QString s_play_time = QString::asprintf("time: %d", play_time);
	QString s_final_score = QString::asprintf("final match score: %d", final_score);

	vector<QString> popup_model = {s_score, s_energy, s_play_time, s_final_score, "close"};
	vector<function<void()>> popup_actions;
	for (unsigned int i=0; i<popup_model.size()-1;i++)
		popup_actions.push_back([this]{return;});
	popup_actions.push_back([this]{this->exit();});

	auto *popup_view = new UiPagePopupWidget_qt(message,
			new UiPageMenuWidget_qt(&popup_model));

	auto popup_menu = new MatchEndPopup(popup_actions, popup_view, popup_model.size()-1);
	popup_menu->setPos(GameConfig::playground_width/2, GameConfig::playground_height/2);
	popup_menu->addToPage(page_view);

	return popup_menu;
}

void GameController::macthEnded(bool gameover){
	int score = GameWorld::instance().getPlayer()->getScore();
	int energy = GameWorld::instance().getPlayer()->getEnergy();
	int play_time = ptime->getPlayTime();
	int final_score = 0;
	QString message;
	if(!gameover){
		final_score = score + energy*10 - play_time/100;
		message = "You WIN!!!";
	}
	else{
		final_score = score;
		message = "GAME OVER!";
	}
	match_end_menu = create_match_ended_popup(score, energy, play_time, final_score, message);
	current_menu = match_end_menu;
}

void GameController::checkMatchRules(){
	if(GameWorld::instance().getPlayer()->isDead()){
		//you loose!
		//remove player
		//stop play time
		//keep monster
		//bleur screen
		is_paused = true; //FIXME need a state
		timer->stop(); //FIXME player destruction not managed
		macthEnded(true);
	}
	if(GameWorld::instance().getMonsters().empty()){
		//you win!
		is_paused = true; //FIXME need a state
		timer->stop();
		macthEnded(false);
	}

}
void GameController::gameStep(){
#ifdef  DEBUG
    QTime t = QTime::currentTime();
    qDebug("iteration %s", t.toString().toStdString().c_str());
    qDebug("-> elapsed %d", e.elapsed());
#endif
    if(!is_paused)
    	checkMatchRules();
    ptime->increase();
    GameWorld::instance().nextFrame();
}

bool GameController::handleKey(int key, bool released){
    bool ret = false;

    switch(key){
    case Qt::Key_Space:
    case Qt::Key_D:
    case Qt::Key_Right:
    case Qt::Key_A:
    case Qt::Key_Left:
    case Qt::Key_Up:
    case Qt::Key_W:
    case Qt::Key_S:
    case Qt::Key_Down:
    case Qt::Key_Enter:
    case Qt::Key_Return:
        if(!is_paused)
        	ret = GameWorld::instance().getPlayer()->handleKey(key, released);
        else{
        	assert(current_menu);
        	ret = current_menu->handleKey(key, released);
        }
        break;
    case Qt::Key_Exit:
    case Qt::Key_Escape:
        if (released) togglePause();
        ret = true;
        break;
    default:
        break;
    }
    return ret;
}

