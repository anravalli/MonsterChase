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

#ifndef Monster_H
#define Monster_H

#include <QGraphicsItem>

#define DEF_ENERGY 50
#define MIN_ENERGY 0
#define MAX_ENERGY 100

typedef enum {
    normal,
    rage_available,
    on_rage,
    dead
} MonsterStates;

typedef enum {
    idle,
    moving
} MonsterSubStates;

enum MonsterDirection {
    Monster_up,
    Monster_down,
    Monster_left,
    Monster_right
};

typedef struct {
    //float energy;
    MonsterStates state;
    MonsterSubStates sub_state;
    int pos_x;
    int pos_y;
    bool direction[4];
    //int score;
} MonsterModel;

class MonsterSm {
public:
    virtual void tick() = 0;
    //virtual void toggleRage() = 0;
    //virtual void enter() = 0;
    //virtual void exit() = 0;
    virtual ~MonsterSm(){}
};

class MonsterShape : public QGraphicsItem
{
public:
    MonsterShape(MonsterModel* m);
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

private:
    QColor color[2];
    int color_idx=0;
    MonsterModel* model;
};

class Monster : public QObject
{
    Q_OBJECT

public:
    Monster(QGraphicsScene * s);
    MonsterShape* getShape(){
        return shape;
    }

    void tick();

    ~Monster();

protected:
    //bool eventFilter(QObject *watched, QEvent *event) Q_DECL_OVERRIDE;

private:
    MonsterModel model = {
        normal, //state
        idle, //sub_state
        100, //pos_x
        100, //pos_y
        {false,false,false,false}, //direction
    };
    MonsterShape* shape;
    MonsterSm* pstates[4]={nullptr,nullptr,nullptr,nullptr};

    void move();
};



#endif // Monster_H
