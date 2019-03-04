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
#include "monster.h"
#include "arena.h"

#define PLAYGROUND_WIDTH 800
#define PLAYGROUND_HEIGHT 800
#define PLAYGROUND_BORDER_WIDTH 50
#define PLAYGROUND_BORDER_HEIGHT 50
#define PLAYGROUND_VIEW_EXTRA_WIDTH 100
#define PLAYGROUND_VIEW_EXTRA_HEIGHT 100
#define PLAYGROUND_VIEW_WIDTH PLAYGROUND_WIDTH + PLAYGROUND_VIEW_EXTRA_WIDTH
#define PLAYGROUND_VIEW_HEIGHT PLAYGROUND_HEIGHT + PLAYGROUND_VIEW_EXTRA_HEIGHT

#define FRAMERATE 1000/50

class GameView : public QGraphicsView
{
public:
    GameView(QGraphicsScene *scene) : QGraphicsView(scene)
    {
        setFocusPolicy(Qt::StrongFocus);
        setDragMode(NoDrag);
        setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
        setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
        setFixedSize(QSize(PLAYGROUND_VIEW_WIDTH,PLAYGROUND_VIEW_HEIGHT));
        inner_border = new QRect(PLAYGROUND_BORDER_WIDTH,
                                 PLAYGROUND_BORDER_HEIGHT,
                                 PLAYGROUND_WIDTH-PLAYGROUND_BORDER_WIDTH,
                                 PLAYGROUND_HEIGHT-PLAYGROUND_BORDER_HEIGHT);
    }

    QRect const * innerBorder(){
        return inner_border;
    }

protected:
    virtual void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE {
#ifdef  DEBUG
        qDebug("Event received by GameView %d (%s)",event->key(), event->text().toStdString().c_str());
#endif
        QGraphicsView::keyPressEvent(event);
        return;
    }
    virtual void resizeEvent(QResizeEvent *) Q_DECL_OVERRIDE
    {
    }
private:
    QRect* inner_border;

};

class PlayTime : public QGraphicsSimpleTextItem
{
public:
    PlayTime()
        :color(255,127,127)
    {
        QFont font("Helvetica",14,QFont::Bold);
        this->setFont(font);
        this->setPen(QPen(color));
    }

    void increase(){
        if(!frame_counter){
            frame_counter=25;
            time++;
        }
        else
            frame_counter--;
        this->setText(QString::asprintf("%04d", time));
        return;
    }

private:
    QColor color;
    PlayerModel* _model;
    int time=0;
    int frame_counter=25;
};

MonsterChase::MonsterChase()
{
    setUpView();

    arena = new Arena(":/resources/map.txt",scene);
    addPlayer();
    addMonster();
    //keep this as the last in order to have it on top of the Z-stack
    addPlayTime();

    connect(arena,SIGNAL(build_complete()),this,SLOT(start()));

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(gameStep()));
    arena->startShowMap();
}

void MonsterChase::show(){
    view->show();
}
void MonsterChase::start(){
    player->show();
    monster->show();
    timer->start(FRAMERATE);
}
void MonsterChase::pause(){
    //player->hide();
    //monster->hide();
    timer->stop();
}

void MonsterChase::setUpView(){
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, PLAYGROUND_WIDTH, PLAYGROUND_WIDTH);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    view = new GameView(scene);
    view->setRenderHint(QPainter::Antialiasing);
    view->setBackgroundBrush(QPixmap(":/resources/textured-stainless-steel-sheet.jpg"));
    view->setCacheMode(QGraphicsView::CacheBackground);
    view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    //view->setDragMode(QGraphicsView::ScrollHandDrag);
    view->setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Monster Chase"));
}

MonsterChase::~MonsterChase()
{
    delete scene;
    delete view;
}

void MonsterChase::addPlayTime(){
    ptime = new PlayTime();
    ptime->setPos(-PLAYGROUND_BORDER_WIDTH/2,-PLAYGROUND_BORDER_HEIGHT*0.6);
    //ptime->hide();
    scene->addItem(ptime);
}

void MonsterChase::addPlayer(){
    player = new Player(scene);
    player->setEnergyGaugePos(PLAYGROUND_WIDTH/2, PLAYGROUND_HEIGHT+PLAYGROUND_BORDER_HEIGHT*0.3);
    player->setScorePos(PLAYGROUND_WIDTH-35,-PLAYGROUND_BORDER_HEIGHT*0.6);
    player->hide();
}

void MonsterChase::addMonster(){
    monster = new Monster::Monster(scene);
    monster->hide();
}

void MonsterChase::gameStep(){
#ifdef  DEBUG
    QTime t = QTime::currentTime();
    qDebug("iteration %s", t.toString().toStdString().c_str());
    qDebug("-> elapsed %d", e.elapsed());
#endif
    //scene->advance();
    ptime->increase();
    player->tick();
    monster->tick();
    //e.restart();

}

