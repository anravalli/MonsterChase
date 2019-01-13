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


Player::Player(QGraphicsScene * s){

    shape = new PlayerShape(&model);
    energy_gauge = new PlayerEnergyGauge(&model);
    //setFocusPolicy(Qt::StrongFocus);
    s->addItem(energy_gauge);
    s->addItem(shape);
    QApplication::instance()->installEventFilter(this);
}

void Player::tick(){
    if (model.energy<MAX_ENERGY && model.state==normal){
        model.energy=model.energy+0.25;
    }
    if(model.energy == MAX_ENERGY)
        model.rage_available = true;
    move();

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
//    if (!released and
//            (key==Qt::Key_D or key==Qt::Key_S or
//             key==Qt::Key_A or key==Qt::Key_W))
//        model.sub_state=moving;
//    else if (released and
//             (key==Qt::Key_D or key==Qt::Key_S or
//              key==Qt::Key_A or key==Qt::Key_W))
//        model.sub_state=idle;

    switch(key){
    case Qt::Key_Space:
#ifdef  DEBUG
        qDebug("--> Handling Spacebar");
#endif
        switch(model.state){
        case normal:
            if (!released and model.rage_available){
#ifdef  DEBUG
                qDebug("%d - rage_available, swtching to on_rage", __LINE__);
#endif
                model.state = on_rage;
                model.rage_available=false;
            }
            break;
        case on_rage:
#ifdef  DEBUG
            qDebug("%d - swtching to running", __LINE__);
#endif
            if (!released) model.state = normal;
            break;
        case dead:
        default:
            break;
        }
        ret = true;
        break;
    case Qt::Key_D:
        //if(model.sub_state==moving) model.pos_x=model.pos_x+5;
        direction[player_right]=!released;
        break;
    case Qt::Key_A:
        //if(model.sub_state==moving) model.pos_x=model.pos_x-5;
        direction[player_left]=!released;
        break;
    case Qt::Key_W:
        direction[player_up]=!released;
        break;
    case Qt::Key_S:
        direction[player_down]=!released;
        break;
    default:
        break;
    }
    return ret;
}

void Player::move(){
    if(direction[player_up])
        model.pos_y=model.pos_y-5;
    if(direction[player_down])
        model.pos_y=model.pos_y+5;
    if(direction[player_left])
        model.pos_x=model.pos_x-5;
    if(direction[player_right])
        model.pos_x=model.pos_x+5;
    return;
}

PlayerShape::PlayerShape(PlayerModel* m)
{
    color[0] = QColor(Qt::green);
    color[1] = QColor(Qt::red);
    model = m;
}

//void PlayerShape::tick()
//{
//    if (_model->state == on_rage)
//        color = QColor(Qt::red);
//    if (_model->state == running)
//        color = QColor(Qt::red);
//    update();
//}


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
        //qDebug("%d running", __LINE__);
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
    //QPoint origin(mapFromScene(0,0));
//    int iteration=0;
//    auto blink = [this, &iteration]()->int {
//            if(iteration==10){
//                color_rage_idx=1-color_rage_idx;
//                iteration = 0;
//            } else
//                iteration++;
//            return color_rage_idx;
//        };

    Q_UNUSED(option);
    Q_UNUSED(widget);
    //draw external rectangle
    painter->setPen(QPen(Qt::black, 2));
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(0,0, 104,20);
    //draw inner rectangle
    painter->setPen(Qt::NoPen);
    if(!model->rage_available)
        painter->setBrush(color);
    else{
        painter->setBrush(color_rage[blink()]);
        //color_rage_idx=1-color_rage_idx;
    }

    painter->drawRect(2,2,(int)model->energy,16);
}
