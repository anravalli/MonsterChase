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
//#include "ui_monsterchase.h"
#include "player.h"

class GameView : public QGraphicsView
{
public:
    GameView(QGraphicsScene *scene) : QGraphicsView(scene)
    {
    }

protected:
//    virtual void resizeEvent(QResizeEvent *) Q_DECL_OVERRIDE
//    {
//    }
};

MonsterChase::MonsterChase()
{
    setUpView();
    addFpsCounter();
    addPlayer();

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(gameStep()));
    timer->start(1000);

    e.start();
}


void MonsterChase::show(){
    view->show();
}

void MonsterChase::setUpView(){
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, 600, 600);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);;
    scene->setSceneRect(0, 0, 600, 600);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    view = new GameView(scene);
    view->setRenderHint(QPainter::Antialiasing);
    //view.setBackgroundBrush(QPixmap(":/images/cheese.jpg"));
    view->setCacheMode(QGraphicsView::CacheBackground);
    view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view->setDragMode(QGraphicsView::ScrollHandDrag);
    view->setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Monster Chase"));
    view->resize(600, 600);
}

MonsterChase::~MonsterChase()
{
    delete scene;
    delete view;
}

void MonsterChase::addFpsCounter(){

}

void MonsterChase::addPlayer(){
    player = new Player(scene);
    QGraphicsItem* p_shape = player->getShape();
    p_shape->setPos(25,25);
    //scene->addItem(p_shape);

    QGraphicsItem* p_gauge = player->getEnergyGauge();
    p_gauge->setPos(10,550);
    //scene->addItem(p_gauge);
}

void MonsterChase::addMonster(){

}

//void MonsterChase::gameStep(){
//    QTime t = QTime::currentTime();
//    qDebug("iteration %s", t.toString().toStdString().c_str());
//    qDebug("-> elapsed %d", e.elapsed());
//    e.restart();

//    int delay = qrand()%1000;
//    if (delay < 1)
//        delay = 1;
//    qDebug("-> delay %d", delay);
//    QThread::msleep(delay);

//    int interval = 1000 - e.elapsed();
//    timer->setInterval(interval < 0 ? 0 : interval);
//}

//void MonsterChase::gameStep(){
//    QTime t = QTime::currentTime();
//    qDebug("iteration %s", t.toString().toStdString().c_str());
//    qDebug("-> elapsed %d", e.elapsed());

//    int delay = qrand()%1000;
//    if (delay < 1)
//        delay = 1;
//    QThread::msleep(delay);
//    qDebug("-> delay %d", delay);
//    int interval = 1000 - e.elapsed();
//    timer->setInterval(interval < 0 ? 0 : interval);
//    e.restart();
//}

void MonsterChase::gameStep(){
    QTime t = QTime::currentTime();
    qDebug("iteration %s", t.toString().toStdString().c_str());
    qDebug("-> elapsed %d", e.elapsed());
    //scene->advance();
    player->tick();
    e.restart();

}

