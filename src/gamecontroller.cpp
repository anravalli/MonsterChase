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
#include "matchendmenu.h"

GameController::GameController(UiPageController *parent):
    UiPageController(parent)
{
    initPageView<GamePage>();

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(gameStep()));

    m_pause_menu = create_pause_menu();

    match_states[ms_running] = MatchStateFactory(ms_running, this);
    match_states[ms_pused] = MatchStateFactory(ms_pused, this);
    match_states[ms_ended] = MatchStateFactory(ms_ended, this);
    match_states[ms_aborted] = MatchStateFactory(ms_aborted, this);

    current_state = ms_aborted;
}

//TODO: removeFromPage() needed
void GameController::initMatch(){
	GameWorld::instance().initLevel(m_match->getMapName());

	Arena* arena = GameWorld::instance().getArena();
	arena->addToPage(page_view);
	connect(arena,SIGNAL(build_complete()),this,SLOT(start()));

	GameWorld::instance().getPlayer()->addToPage(page_view);
	for(auto m: GameWorld::instance().getMonsters())
		m->addToPage(page_view);
	m_pause_menu->addToPage(page_view);
}

void GameController::show(){
	//start a new match
	initMatch();
    UiPageController::show();
    GameWorld::instance().getArena()->show();
}

void GameController::start(){
    addPlayTime(); //test
    change_match_state(ms_running);
	GameWorld::instance().start();
	timer->start(GameConfig::game_update_period);
}

//for game states: start here
void GameController::exit(){
	qDebug("GameController::exit()");
	timer->stop();
	GameWorld::instance().getArena()->removeFromPage(page_view);
	GameWorld::instance().getPlayer()->removeFromPage(page_view);
	for(auto m: GameWorld::instance().getMonsters())
		m->removeFromPage(page_view);
	page_view->removeItem(ptime);
	GameWorld::instance().deInitLevel();

	m_pause_menu->hide();
	m_pause_menu->removeFromPage(page_view);
	if(m_end_menu) {
		m_end_menu->hide();
		delete m_end_menu;
		m_end_menu = nullptr;
	}
	UiPageController::exit();
}

//destructor currently unused
GameController::~GameController()
{
	delete page_view;
    delete ptime;
    delete timer;
    delete m_pause_menu;
    if(m_end_menu){
    	delete m_end_menu;
        m_end_menu = nullptr;
    }
}

void GameController::addPlayTime(){
    ptime = new PlayTime();
    ptime->setPos(-GameConfig::playground_border_width/2,
                  -GameConfig::playground_border_height*0.6);
    page_view->addItem(ptime);
}


void GameController::gameStep(){
    match_states[current_state]->next();
    ptime->setTime(m_match->getPlayTime());
}

bool GameController::handleKey(int key, bool released){
    return match_states[current_state]->handleKey(key, released);
}

void GameController::change_match_state(MatchStateE next_state){
	match_states[current_state]->exit();
	current_state = next_state;
	match_states[current_state]->enter();
}

UiPageMenu *GameController::create_pause_menu()
{
	vector<QString> popup_model = {"yes", "not"};
	vector<function<void()>> popup_actions;
	popup_actions.push_back([this]{this->exit();});
	popup_actions.push_back([this]{this->change_match_state(ms_running);});

	auto *popup_view = new UiPagePopupWidget_qt(QString("Do you want to leave the match?"),
			new UiPageMenuWidget_qt(&popup_model));

	auto popup_menu = new UiPageMenu(popup_actions, popup_view, 1);
	popup_menu->setPos(GameConfig::playground_width/2, GameConfig::playground_height/2);
	popup_menu->hide();

	return popup_menu;
}

UiPageMenu *GameController::create_match_ended_popup()
{
	//temporary using a standard popup menu
	QString s_score = QString::asprintf("score: %d", m_match->getPlayerScore());
	QString s_energy = QString::asprintf("energy: %d", m_match->getPlayerEnergy());
	QString s_play_time = QString::asprintf("time: %d", m_match->getPlayTime());
	QString s_final_score = QString::asprintf("final match score: %d", m_match->compute_match_score());

	vector<QString> popup_model = {s_score, s_energy, s_play_time, s_final_score, "close"};
	vector<function<void()>> popup_actions;
	for (unsigned int i=0; i<popup_model.size()-1;i++)
		popup_actions.push_back([this]{return;});
	popup_actions.push_back([this]{this->exit();});

	auto *popup_view = new UiPagePopupWidget_qt(m_match->get_match_completion_prompt(),
			new UiPageMenuWidget_qt(&popup_model));

	auto popup_menu = new MatchEndPopup(popup_actions, popup_view, popup_model.size()-1);
	popup_menu->setPos(GameConfig::playground_width/2, GameConfig::playground_height/2);
	popup_menu->addToPage(page_view);

	return popup_menu;
}

UiPageMenu *GameController::end_menu(){
	if(m_end_menu == nullptr)
		m_end_menu = create_match_ended_popup();
	return m_end_menu;
};


