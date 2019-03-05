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

#ifndef PLAYERQTVIEWS_H
#define PLAYERQTVIEWS_H

#include <QGraphicsItem>

#include "player.h"

class PlayerShape : public QGraphicsItem
{
public:
    PlayerShape(PlayerModel* m);
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

protected:
//    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
//    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
//    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;

private:
    QColor color[2];
    int color_idx=0;
    int blink_delay=BLINK_DELAY;
    PlayerModel* model;

    int blink();
};

class PlayerEnergyGauge : public QGraphicsItem
{
public:
    PlayerEnergyGauge(PlayerModel* m);
    void setEnergy(int e);
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

private:
    QColor color;
    QColor color_rage[2];
    int color_rage_idx = 0;
    PlayerModel * model;

    int iteration = 0;
    int blink();

};

class PlayerScore : public QGraphicsSimpleTextItem
{
public:
    PlayerScore(PlayerModel* m);

    void updateScore();

protected:

private:
    PlayerModel* _model;
};




#endif // PLAYERQTVIEWS_H
