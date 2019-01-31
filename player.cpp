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

#include <QtWidgets>
#include "player.h"


class PlayerNormal: public PlayerSm {
public:
    PlayerNormal(PlayerModel* model)
        :_model(model){
        _speed_45 = _speed/sqrt(2);
    }

    virtual void tick(){
        _model->energy=_model->energy+0.125;
        if(_model->energy == MAX_ENERGY)
            _model->state = rage_available;
        move();
    }
    virtual void toggleRage(){}
    virtual ~PlayerNormal(){}

private:
    int _speed=3;
    double _speed_45=0;
protected:
    PlayerModel* _model;

    void move(){
        double speed = _speed;
        if((_model->direction[player_up] or _model->direction[player_down])
                and (_model->direction[player_left] or _model->direction[player_right])){
            speed = _speed_45;
        }
        if(_model->direction[player_up])
            _model->pos_y=_model->pos_y-speed;
        if(_model->direction[player_down])
            _model->pos_y=_model->pos_y+speed;
        if(_model->direction[player_left])
            _model->pos_x=_model->pos_x-speed;
        if(_model->direction[player_right])
            _model->pos_x=_model->pos_x+speed;
        return;
    }
};

class PlayerRageAvailable: public PlayerNormal {
public:
    PlayerRageAvailable(PlayerModel* model)
        :PlayerNormal(model){}
    virtual void tick(){
        move();
    }
    virtual void toggleRage(){
        _model->state=on_rage;
    }
};

class PlayerOnRage: public PlayerSm {
public:
    PlayerOnRage(PlayerModel* model)
        :_model(model){
        _speed_45 = _speed/sqrt(2);
    }

    virtual void tick(){
        _model->energy=_model->energy-0.125;
        if(_model->energy == DEF_ENERGY)
            _model->state = normal;
        move();
    }
    virtual void toggleRage(){
        _model->state=normal;
    }
    virtual ~PlayerOnRage(){}
private:
    PlayerModel* _model;
    int _speed=5;
    double _speed_45=0;

    void move(){
        float speed = _speed;
        if((_model->direction[player_up] or _model->direction[player_down])
                and (_model->direction[player_left] or _model->direction[player_right])){
            speed = _speed_45;
        }
        if(_model->direction[player_up])
            _model->pos_y=_model->pos_y-speed;
        if(_model->direction[player_down])
            _model->pos_y=_model->pos_y+speed;
        if(_model->direction[player_left])
            _model->pos_x=_model->pos_x-speed;
        if(_model->direction[player_right])
            _model->pos_x=_model->pos_x+speed;
        return;
    }
};

class PlayerDead: public PlayerSm {
public:
    PlayerDead(PlayerModel* model)
        :_model(model){}

    virtual void tick(){}
    virtual void toggleRage(){}
    virtual ~PlayerDead(){}
private:
    PlayerModel* _model;
};

class PlayerScore : public QGraphicsSimpleTextItem
{
public:
    PlayerScore(PlayerModel* m)
        :_model(m)
    {
        this->setPen(QPen(Qt::blue));
        QFont font("Helvetica",14,QFont::Bold);
        this->setFont(font);
        this->setBrush(Qt::white);
        this->setText(QString::asprintf("%06d", _model->score));
    }

//    QRectF boundingRect() const Q_DECL_OVERRIDE{
//        return QRectF(0,0,16,80);
//    }

//    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE{
//        Q_UNUSED(option);
//        Q_UNUSED(widget);

//        painter->setPen(Qt::blue);
//        QFont font("Helvetica",14,QFont::Bold);
//        painter->setFont(font);
//        painter->setBrush(Qt::NoBrush);
//        painter->drawText(QPoint(0,0), QString::asprintf("%06d", _model->score));
//    }

protected:

private:
    PlayerModel* _model;
};

Player::Player(QGraphicsScene * s){

    shape = new PlayerShape(&model);
    energy_gauge = new PlayerEnergyGauge(&model);
    score = new PlayerScore(&model);

    //init state machine
    pstates[normal] = new PlayerNormal(&model);
    pstates[rage_available] = new PlayerRageAvailable(&model);
    pstates[on_rage] = new PlayerOnRage(&model);
    pstates[dead] = new PlayerDead(&model);
    //the order we add the items to the scene affects the z-order
    s->addItem(shape);
    s->addItem(score);
    s->addItem(energy_gauge);
    //score->setPos((s->sceneRect()).width()-35, -50*0.6);
    QApplication::instance()->installEventFilter(this);
}

void Player::tick(){
    pstates[model.state]->tick();

    energy_gauge->update();
    shape->setPos(model.pos_x,model.pos_y);
    shape->update();
#ifdef  DEBUG
    qDebug("Player energy %d", model.energy);
#endif
}

bool Player::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
        //qDebug("%d KeyPress received by Player", __LINE__);
        QKeyEvent* ke = static_cast<QKeyEvent*>(event);
        int key = ke->key();
        return handleKey(key, false);
    } else  if (event->type() == QEvent::KeyRelease) {
        QKeyEvent* ke = static_cast<QKeyEvent*>(event);
        int key = ke->key();
        return handleKey(key, true);
    }
    // Make sure the rest of events are handled
    return QObject::eventFilter(watched, event);
}

bool Player::handleKey(int key, bool released){
    bool ret = false;

    switch(key){
    case Qt::Key_Space:
#ifdef  DEBUG
        qDebug("--> Handling Spacebar");
#endif
        if(!released)pstates[model.state]->toggleRage();
        ret = true;
        break;
    case Qt::Key_D:
        model.direction[player_right]=!released;
        break;
    case Qt::Key_A:
        model.direction[player_left]=!released;
        break;
    case Qt::Key_W:
        model.direction[player_up]=!released;
        break;
    case Qt::Key_S:
        model.direction[player_down]=!released;
        break;
    default:
        break;
    }
    return ret;
}

void Player::setScorePos(int x, int y){
    score->setPos(x,y);
}

Player::~Player(){
    delete pstates[normal];
    delete pstates[on_rage];
    delete pstates[dead];
    //TODO: check wether the QGraphicsItems are deleted by the QGraphicsScene
    // they belongs to
    delete shape;
    delete energy_gauge;
}

/*
 * PlayerShape methods implementation
 */

PlayerShape::PlayerShape(PlayerModel* m)
{
    color[0] = QColor(Qt::yellow);
    color[1] = QColor(Qt::red);
    model = m;
}

QRectF PlayerShape::boundingRect() const
{
    return QRectF(-15.5, -15.5, 34, 34);
}

void PlayerShape::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    switch(model->state){
    case on_rage:
        //qDebug("%d on_rage", __LINE__);
        color_idx = 1;
        break;
    case normal:
        //qDebug("%d normal", __LINE__);
        color_idx = 0;
        break;
    default:
        break;
    }
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::darkGray);
    painter->drawEllipse(-12, -12, 30, 30);
    painter->setPen(QPen(Qt::black, 1));
    painter->setBrush(QBrush(color[color_idx]));
    painter->drawEllipse(-15, -15, 30, 30);
}


PlayerEnergyGauge::PlayerEnergyGauge(PlayerModel *m)
    :model(m)
{
    color = QColor(0,255,0,127);
    color_rage[0] = QColor(255,0,0,127);
    color_rage[1] = QColor(255,100,0,127);
    color_rage_idx = 0;
}


QRectF PlayerEnergyGauge::boundingRect() const
{
    return QRectF(0,0, 104,20);
}

int PlayerEnergyGauge::blink()
{
    if(iteration==4){
        color_rage_idx=1-color_rage_idx;
        iteration = 0;
    } else
        iteration++;
    return color_rage_idx;
}

void PlayerEnergyGauge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    Q_UNUSED(option);
    Q_UNUSED(widget);
    //draw external rectangle
    painter->setPen(QPen(Qt::black, 2));
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(0,0, 104,20);
    //draw inner rectangle
    painter->setPen(Qt::NoPen);
    if(model->state == rage_available)
        painter->setBrush(color_rage[blink()]);
    else if(model->state == on_rage)
        painter->setBrush(color_rage[0]);
    else{
        painter->setBrush(color);
    }

    painter->drawRect(2,2,(int)model->energy,16);
}
