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

#include <qobject.h>

class MonsterChase;
class Player;

class QGraphicsItem;

namespace Monster{

class MonsterShape;
class MonsterSight;
class MonsterSm;

    enum MonsterStates {
        patrol,
        attack,
        flee
    } ;

    enum MonsterSubStates {
        route,
        move,
        freeze
    } ;

    enum MonsterDirection {
        Monster_up,
        Monster_down,
        Monster_left,
        Monster_right
    };

    enum MonsterType {
        Blinky,
        Pinky,
        Inky,
        Clyde
    };

    struct MonsterModel{
        MonsterType type;
        MonsterStates state;
        MonsterSubStates sub_state;
        float pos_x;
        float pos_y;
        float direction;
        float target_direction;
    } ;

    class Monster;
    Monster* monsterFactory(MonsterType mtype, MonsterChase *w, QPointF pos);

    class Monster : public QObject
    {
        Q_OBJECT


    public:
        void show();

        void hide();

        QRectF collisionBox() const;

        void update();

        MonsterModel* getModel();

        friend Monster* monsterFactory(MonsterType mtype, MonsterChase *w, QPointF pos);

        ~Monster();

    protected:
        //bool eventFilter(QObject *watched, QEvent *event) Q_DECL_OVERRIDE;
        void addViewComponent(QGraphicsItem* componet);

    private:
        Monster(MonsterChase* world);
        MonsterChase* world;
        MonsterModel model = {
            MonsterType::Blinky, //type
            MonsterStates::patrol, //state
            MonsterSubStates::move, //sub_state
            200, //pos_x
            200, //pos_y
            0, //direction
            0 //target direction
        };
        MonsterShape* shape=0;
        MonsterSight* sight=0;
        MonsterSm* mstates[3]={nullptr,nullptr,nullptr};

        void checkCollisionsWithPlayer();
        QRectF getIntersectonWith(Player *p);
        void checkCollisionsWithWalls();
    };

//    class MonsterFactory {
//    public:
//        static Monster* buildMonster(MonsterType mtype, MonsterChase *w, QPointF pos);
//    };

} //namescpace Monster

#endif // Monster_H
