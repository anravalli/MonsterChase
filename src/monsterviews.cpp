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

#include "monsterviews.h"

namespace Monster{
/*
 * MonsterShape methods implementation
 */

MonsterShape::MonsterShape(MonsterModel* m)
{
    color[patrol] = QColor(0,127,127);
    color[attack] = QColor(255,50,127);
    color[flee] = QColor(0,127,255);
    model = m;
}

QRectF MonsterShape::boundingRect() const
{
    return QRectF(-15.5, -15.5, 34, 34);
}

void MonsterShape::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::darkGray);
    painter->drawRect(-12, -12, 30, 30);
    painter->setPen(QPen(Qt::black, 1));
    painter->setBrush(QBrush(color[model->state]));
    painter->drawRect(-15, -15, 30, 30);
    painter->setPen(Qt::NoPen);
    //temp
    //painter->setBrush(QBrush(QColor(0,255,50,50)));
    //painter->drawPie(-100,-165,200,300,50*16,80*16);
}

QRectF MonsterSight::boundingRect() const {
    return QRectF(-100,-165,200,300);
}

void MonsterSight::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setBrush(QBrush(QColor(0,255,50,50)));
    painter->drawPie(-100,-165,200,300,50*16,80*16);
}

}
