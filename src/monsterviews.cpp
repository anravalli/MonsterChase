/*
 *	Monster Chase: a testing playground for behaviors trees
 *
 *	Copyright 2019-2021 Andrea Ravalli <anravalli @ gmail.com>
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
#include "ui/uipageview_qt.h"

#define VIEW_DEBUG 0

namespace Monster{
/*
 * MonsterShape methods implementation
 */

MonsterView *monsterViewFactory(MonsterType type, MonsterModel* model)
{
    MonsterView* monster = new MonsterView(model);
    //type related elements
    switch (type){
    case Blinky:
        //set shapes
        monster->shape = new MonsterShape(model);
        monster->sight = new MonsterSight(model);
        break;
    case Pinky:
        //set shapes
        monster->shape = new MonsterTriangularShape(model);
        monster->sight = new MonsterSight(model);
        break;
    case Inky:
        //set shapes
        monster->shape = new MonsterShape(model);
        monster->sight = new MonsterSight(model);
        break;
    case Clyde:
        //set shapes
        monster->shape = new MonsterTriangularShape(model);
        monster->sight = new MonsterSight(model);
        break;
    }

    return monster;
}

void MonsterView::addToPage(UiPageViewQt* page)
{
    //adding views to scene
    //the order we add the items to the scene affects the z-order
    page->addItem(this->shape);
    page->addItem(this->sight);
    return;
}

void MonsterView::show()
{
    shape->show();
    sight->show();
}

void MonsterView::hide()
{
    shape->hide();
    sight->hide();
}

void MonsterView::setPosition(double x, double y)
{
    shape->setPos(x,y);
    sight->setPos(x,y);
}

void MonsterView::setRotation(double direction)
{
    shape->setRotation(direction);
    sight->setRotation(direction+90);
}

void MonsterView::update()
{
    setPosition(model->pos_x,model->pos_y);
    setRotation(model->direction);
    shape->update();
    sight->update();
}

void MonsterView::updateGeometry(double x, double y, double scale, double direction)
{
    Q_UNUSED(scale);

    shape->setPos(x,y);
    sight->setPos(x,y);
    shape->setRotation(direction);
    sight->setRotation(direction+90);
    shape->update();
    sight->update();
}

MonsterView::MonsterView(MonsterModel* model):
    model(model)
{

}

MonsterView::~MonsterView()
{
    //TODO: check wether the QGraphicsItems are deleted by the QGraphicsScene
    // they belongs to
    delete shape;
    delete sight;
}

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
}

MonsterTriangularShape::MonsterTriangularShape(MonsterModel *m)
{
    color[patrol] = QColor(125,0,127);
    color[attack] = QColor(255,50,127);
    color[flee] = QColor(0,127,255);
    model = m;
}

void MonsterTriangularShape::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::darkGray);
    QPointF shadow[] = {QPointF(18 ,3), QPointF(-12, 18), QPointF(-12, -18)};
    painter->drawPolygon( shadow, 3);
    painter->setPen(QPen(Qt::black, 1));
    painter->setBrush(QBrush(color[model->state]));
    QPointF shape[] = {QPointF(15, 0), QPointF(-15, 15), QPointF(-15,-15)};
    painter->drawPolygon( shape, 3);
    painter->setPen(Qt::NoPen);
}

QRectF MonsterSight::boundingRect() const {

#if VIEW_DEBUG
    return QRectF(-100,-165,200,300);
#else
    return QRectF(-100, -165, 200, 265);
#endif
}

void MonsterSight::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setBrush(QBrush(QColor(0,255,50,50)));
    painter->drawPie(-100,-165,200,300,50*16,80*16);

#if VIEW_DEBUG
    //player detection box
    painter->setBrush(QBrush(QColor(255,0,0,50)));
    painter->drawRect(-65,-165,130,150);
    //warning box
#else
    painter->setPen(Qt::NoPen);
#endif
    painter->setBrush(QBrush(QColor(250,255,0,50)));
    painter->drawEllipse(-100,-100,200,200);
}

}
