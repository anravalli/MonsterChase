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

#include "ui/uipage_qt.h"
#include "gamecontroller.h"
#include "gameviews.h"
#include "gameworld.h"
#include "gameconfig.h"
#include "arena.h"
#include "player.h"
#include "monster.h"

#define FRAMERATE 50
#define UPDATE_PERIOD 1000/FRAMERATE


GameController::GameController(QObject *parent) : QObject(parent)
{
    //setUpView();

    page = new UiPageQt();
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(gameStep()));

    /*
     * As of now there is only one level and we init right in
     * GameController constructor
     */
    QString map = ":/resources/map.txt";
    GameWorld::instance().initLevel(map);

    Arena* arena = GameWorld::instance().getArena();
    arena->addToPage(page);
    connect(arena,SIGNAL(build_complete()),this,SLOT(start()));
    arena->show();

    GameWorld::instance().getPlayer()->addToPage(page);
    for(auto m: GameWorld::instance().getMonsters())
        m->addToPage(page);
}


void GameController::show(){
    page->show();
}

void GameController::start(){
    addPlayTime(); //test

    GameWorld::instance().start();
    timer->start(UPDATE_PERIOD);
}

void GameController::pause(){
    timer->stop();
}


GameController::~GameController()
{
    delete page;
}

void GameController::addPlayTime(){
    ptime = new PlayTime(FRAMERATE);
    ptime->setPos(-GameConfig::playground_border_width/2,
                  -GameConfig::playground_border_height*0.6);
    page->addItem(ptime);
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

