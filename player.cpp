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
    s->addItem(energy_gauge);
    s->addItem(shape);
}

void Player::tick(){
    if (model.energy<MAX_ENERGY && model.state==running){
        model.energy++;
    }
    if(model.energy == MAX_ENERGY)
        model.rage_available = true;
    energy_gauge->update();
    shape->update();
    qDebug("Player energy %d", model.energy);
}

bool Player::event(QEvent* ev)
{
    qDebug("Event received by Player");
    if (ev->type() == QEvent::KeyPress) {
        qDebug("KeyPress received by Player");
        QKeyEvent* ke = static_cast<QKeyEvent*>(ev);
        int key = ke->key();
        handleKey(key, false);
        return true;
    } else  if (ev->type() == QEvent::KeyRelease) {
        QKeyEvent* ke = static_cast<QKeyEvent*>(ev);
        int key = ke->key();
        handleKey(key, true);
        return true;
    }
    // Make sure the rest of events are handled
    return QObject::event(ev);
}

void Player::handleKey(int key, bool released){
    switch(key){
    case Qt::Key_Space:
        if (model.rage_available){
            model.state = on_rage;
            model.rage_available=false;
        }
        if(model.state == on_rage){
            model.state = running;
        }
        break;
    default:
        break;
    }
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
        color_idx = 1;
        break;
    case running:
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

void PlayerEnergyGauge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //QPoint origin(mapFromScene(0,0));

    Q_UNUSED(option);
    Q_UNUSED(widget);
    //draw external rectangle
    painter->setPen(QPen(Qt::black, 2));
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(0,0, 104,20);
    //draw inner rectangle
    qDebug("energy %d", model->energy);
    painter->setPen(Qt::NoPen);
    if(!model->rage_available)
        painter->setBrush(color);
    else{
        painter->setBrush(color_rage[color_rage_idx]);
        color_rage_idx=1-color_rage_idx;
    }

    painter->drawRect(2,2,model->energy,16);
}
