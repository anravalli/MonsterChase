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
    normal,
    on_rage,
    dead
} PlayerStates;

typedef enum {
    idle,
    moving
} PlayerSubStates;

enum PlayerDirection {
    player_up,
    player_down,
    player_left,
    player_right
};

typedef struct {
    float energy;
    PlayerStates state;
    PlayerSubStates sub_state;
    int pos_x;
    int pos_y;
    bool rage_available;
} PlayerModel;

class PlayerSm {
public:
    //virtual PlayerSm(PlayerModel* model) = 0;
    virtual void tick() = 0;
    virtual void enter() = 0;
    virtual ~PlayerSm(){}
};

class PlayerRunning: PlayerSm {
public:
    PlayerRunning(PlayerModel* model)
        :_model(model){}

    virtual void tick();
    virtual void enter();
    virtual ~PlayerRunning(){}
private:
    PlayerModel* _model;
};

class PlayerOnRage: PlayerSm {
public:
    PlayerOnRage(PlayerModel* model)
        :_model(model){}

    virtual void tick();
    virtual void enter();
    virtual ~PlayerOnRage(){}
private:
    PlayerModel* _model;
};

class PlayerDead: PlayerSm {
public:
    PlayerDead(PlayerModel* model)
        :_model(model){}

    virtual void tick();
    virtual void enter();
    virtual ~PlayerDead(){}
private:
    PlayerModel* _model;
};

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
    PlayerModel* model;
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
    //bool event(QEvent* ev) Q_DECL_OVERRIDE;
    bool eventFilter(QObject *watched, QEvent *event) Q_DECL_OVERRIDE;

private:
    PlayerModel model = {DEF_ENERGY,normal,idle,25,25,false};
    PlayerShape* shape;
    PlayerEnergyGauge* energy_gauge;
    bool direction[4]={false,false,false,false};

    void move();
    bool handleKey(int key, bool released);
};



#endif // PLAYER_H
