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

    typedef struct {
        MonsterStates state;
        MonsterSubStates sub_state;
        int pos_x;
        int pos_y;
        int direction;
    } MonsterModel;

    class Monster : public QObject
    {
        Q_OBJECT

    public:
        Monster(MonsterChase* world);
        void show();

        void hide();

        QRectF collisionBox() const;

        void update();

        MonsterModel* getModel();

        ~Monster();

    protected:
        //bool eventFilter(QObject *watched, QEvent *event) Q_DECL_OVERRIDE;

    private:
        MonsterChase* world;
        MonsterModel model = {
            patrol, //state
            MonsterSubStates::move, //sub_state
            200, //pos_x
            200, //pos_y
            0, //direction
        };
        MonsterShape* shape=0;
        MonsterSight* sight=0;
        MonsterSm* mstates[3]={nullptr,nullptr,nullptr};

        void checkCollisionsWithPlayer();
        QRectF getIntersectonWith(Player *p);
        void checkCollisionsWithWalls();
    };

} //namescpace Monster

#endif // Monster_H
