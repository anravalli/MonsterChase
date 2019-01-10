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

#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsItem>

#define DEF_ENERGY 50
#define MIN_ENERGY 0
#define MAX_ENERGY 100

typedef enum {
    running,
    on_rage,
    dead
} PlayerStates;

typedef struct {
    int energy;
    PlayerStates state;
    int pos_x;
    int pos_y;
} PlayerModel;

class PlayerShape : public QGraphicsItem
{
public:
    PlayerShape();
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

protected:
//    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
//    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
//    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;

private:
    QColor color;
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
    PlayerModel * model;
};

class Player : public QObject
{
    Q_OBJECT

public:
    Player(QGraphicsScene * s);
    PlayerShape* getShape(){
        return shape;
    }
    PlayerEnergyGauge* getEnergyGauge(){
        return energy_gauge;
    }

    void tick();

protected:

private:
    PlayerModel model = {DEF_ENERGY,running,25,25};
    PlayerShape* shape;
    PlayerEnergyGauge* energy_gauge;
};



#endif // PLAYER_H
