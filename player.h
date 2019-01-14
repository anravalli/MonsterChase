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
    rage_available,
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
    bool direction[4];
    int score;
} PlayerModel;

class PlayerSm {
public:
    virtual void tick() = 0;
    virtual void toggleRage() = 0;
    //virtual void enter() = 0;
    //virtual void exit() = 0;
    virtual ~PlayerSm(){}
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

class PlayerScore;

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

    ~Player();

protected:
    bool eventFilter(QObject *watched, QEvent *event) Q_DECL_OVERRIDE;

private:
    PlayerModel model = {
        DEF_ENERGY, //energy
        normal, //state
        idle, //sub_state
        100, //pos_x
        100, //pos_y
        {false,false,false,false}, //direction
        0 // score
    };
    PlayerShape* shape;
    PlayerEnergyGauge* energy_gauge;
    PlayerScore* score;
    //bool direction[4]={false,false,false,false};
    PlayerSm* pstates[4]={nullptr,nullptr,nullptr,nullptr};

    void move();
    bool handleKey(int key, bool released);
};



#endif // PLAYER_H
