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

#define FRAMERATE 50
#define UPDATE_PERIOD 1000/FRAMERATE


GameController::GameController(UiPageController *parent):
    UiPageController(parent), is_paused(true)
{
    initPageView<GamePage>();

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(gameStep()));

    /*
     * As of now there is only one level and we init right in
     * GameController constructor
     */
    QString map = ":/resources/map.txt";
    GameWorld::instance().initLevel(map);

    Arena* arena = GameWorld::instance().getArena();
    arena->addToPage(page_view);
    connect(arena,SIGNAL(build_complete()),this,SLOT(start()));

    GameWorld::instance().getPlayer()->addToPage(page_view);
    for(auto m: GameWorld::instance().getMonsters())
        m->addToPage(page_view);
}

void GameController::show(){
    UiPageController::show();
    GameWorld::instance().getArena()->show();
}

void GameController::start(){
    addPlayTime(); //test

    GameWorld::instance().start();
    timer->start(UPDATE_PERIOD);

    is_paused = false;
}

void GameController::exit(){
    qDebug("GameController::exit()");
    qDebug("is_paused %d", is_paused);
    if(is_paused)
        UiPageController::exit();
    timer->stop();
    is_paused = true;
}

GameController::~GameController()
{
    delete page_view;
}

void GameController::addPlayTime(){
    ptime = new PlayTime(FRAMERATE);
    ptime->setPos(-GameConfig::playground_border_width/2,
                  -GameConfig::playground_border_height*0.6);
    page_view->addItem(ptime);
}

void GameController::gameStep(){
#ifdef  DEBUG
    QTime t = QTime::currentTime();
    qDebug("iteration %s", t.toString().toStdString().c_str());
    qDebug("-> elapsed %d", e.elapsed());
#endif
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
        ret = GameWorld::instance().getPlayer()->handleKey(key, released);
        break;
    case Qt::Key_Exit:
    case Qt::Key_Escape:
        if (released) exit();
        ret = true;
        break;
    default:
        break;
    }
    return ret;
}

