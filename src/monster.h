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

#include <QtWidgets>
#include <QGraphicsItem>

 namespace Monster{

    typedef enum {
        patrol,
        attack,
        flee
    } MonsterStates;

    typedef enum {
        moving,
        scanning
    } MonsterSubStates;

    enum MonsterDirection {
        Monster_up,
        Monster_down,
        Monster_left,
        Monster_right
    };

    typedef struct {
        MonsterStates state;
        MonsterSubStates sub_state;
        int pos_x;
        int pos_y;
        int direction;
        //bool direction[4];
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
        QColor color[3];
        MonsterModel* model;
    };

    class MonsterSight : public QGraphicsItem
    {
    public:
        MonsterSight(MonsterModel* m)
            :model(m){};
        QRectF boundingRect() const Q_DECL_OVERRIDE{
            return QRectF(-100,-165,200,300);
        }
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE{
            Q_UNUSED(option);
            Q_UNUSED(widget);

            painter->setBrush(QBrush(QColor(0,255,50,50)));
            painter->drawPie(-100,-165,200,300,50*16,80*16);
        }

    private:
        MonsterModel* model;
    };

    class Monster : public QObject
    {
        Q_OBJECT

    public:
        Monster(QGraphicsScene * s);
        void show(){
            shape->show();
            sight->show();
        }
        void hide(){
            shape->hide();
            sight->hide();
        }
//        MonsterShape* getShape(){
//            return shape;
//        }
//        MonsterSight* getSight(){
//            return sight;
//        }
        void tick();

        ~Monster();

    protected:
        //bool eventFilter(QObject *watched, QEvent *event) Q_DECL_OVERRIDE;

    private:
        MonsterModel model = {
            patrol, //state
            MonsterSubStates::moving, //sub_state
            200, //pos_x
            200, //pos_y
            0, //direction
        };
        MonsterShape* shape=0;
        MonsterSight* sight=0;
        MonsterSm* mstates[3]={nullptr,nullptr,nullptr};

        void move();
    };

} //namescpace Monster

#endif // Monster_H
