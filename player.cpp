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

    shape = new PlayerShape();
    energy_gauge = new PlayerEnergyGauge(&model);
    s->addItem(energy_gauge);
    s->addItem(shape);
}

void Player::tick(){
    if (model.energy<MAX_ENERGY){
        model.energy++;
    }
    energy_gauge->update();
    qDebug("Player energy %d", model.energy);
}

PlayerShape::PlayerShape()
    : color(qrand() % 256, qrand() % 256, qrand() % 256)
{
}


QRectF PlayerShape::boundingRect() const
{
    return QRectF(-15.5, -15.5, 34, 34);
}

void PlayerShape::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::darkGray);
    painter->drawEllipse(-12, -12, 30, 30);
    painter->setPen(QPen(Qt::black, 1));
    painter->setBrush(QBrush(color));
    painter->drawEllipse(-15, -15, 30, 30);
}


PlayerEnergyGauge::PlayerEnergyGauge(PlayerModel *m)
    :model(m)
{
    color = QColor(0,255,0,127);
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
    painter->setBrush(color);
    painter->drawRect(2,2,model->energy,16);
}
