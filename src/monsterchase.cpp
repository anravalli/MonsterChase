/*
 *	Monster Chase: a testing playground for behaviors trees
 *
 *	Copyright 2019 Andrea Ravalli <anravalli @ gmail.com>
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

#include "monsterchase.h"
#include "gameworld.h"
#include "gameconfig.h"
#include "arena.h"

#define FRAMERATE 1000/50

MonsterChase::MonsterChase()
{
    setUpView();

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(gameStep()));

    /*
     * As of now there is only one level and we init right in
     * MonsterChase constructor
     */
    QString map = ":/resources/map.txt";
    Arena* arena = new Arena(map, scene);
    connect(arena,SIGNAL(build_complete()),this,SLOT(start()));
    GameWorld::instance().initLevel(arena);
}

void MonsterChase::show(){
    view->show();
}

void MonsterChase::start(){
    addPlayTime(); //test

    GameWorld::instance().start();
    timer->start(FRAMERATE);
}

void MonsterChase::pause(){
    timer->stop();
}

void MonsterChase::setUpView(){
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, GameConfig::playground_width, GameConfig::playground_width);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    view = new GameView(scene);
    view->setRenderHint(QPainter::Antialiasing);
    view->setBackgroundBrush(QPixmap(":/resources/textured-stainless-steel-sheet.jpg"));
    view->setCacheMode(QGraphicsView::CacheBackground);
    view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view->setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Monster Chase"));

    //TO BE REVIEWED
    GameWorld::instance().setScene(scene);
}

MonsterChase::~MonsterChase()
{
    delete scene;
    delete view;
}

void MonsterChase::addPlayTime(){
    ptime = new PlayTime();
    ptime->setPos(-GameConfig::playground_border_width/2,
                  -GameConfig::playground_border_height*0.6);
    scene->addItem(ptime);
}

void MonsterChase::gameStep(){
#ifdef  DEBUG
    QTime t = QTime::currentTime();
    qDebug("iteration %s", t.toString().toStdString().c_str());
    qDebug("-> elapsed %d", e.elapsed());
#endif
    ptime->increase();
    GameWorld::instance().nextFrame();
}

