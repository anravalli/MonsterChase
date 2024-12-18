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
#include "base_game/game_entity.h"

class MonsterChase;
class GameWorld;
class Player;
class Animation;

class QGraphicsItem;

namespace Monster{

class MonsterView;
class MonsterSm;

    enum MonsterStates {
        patrol,
        attack,
        flee,
        dead
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
        int id;
        MonsterType type;
        MonsterStates state;
        MonsterSubStates sub_state;
        double pos_x;
        double pos_y;
        double prev_pos_x;
        double prev_pos_y;
        double direction;
        double target_x;
        double target_y;
        double target_direction;
        int curent_speed;

        int health;
        int score_point;
        int death_score_bonus;
        int damage_inflicted_per_hit;
        int damage_suffered_per_hit;

        bool health_gouge_visible;

        Animation *current_animation;
    } ;

    class Monster;
    Monster* monsterFactory(MonsterType mtype, QPointF pos);

    class Monster : public QObject, public GameEntityI
    {
        Q_OBJECT

        friend Monster* monsterFactory(MonsterType mtype, QPointF pos);

    public:
        void show() override;
        void hide() override;
        virtual void addToPage(UiPageViewQt* page) override;
        virtual void removeFromPage(UiPageViewQt* page) override;

        QRectF collisionBox() const;
        QRectF sightBox() const;
        QRectF warningBox() const;

        void update();
        int id();
        int hit_suffered(); //return score points
        int hit_inflicted(); //return score points

        MonsterStates getState(){return model.state;}
        bool isAlive();

        virtual ~Monster();

    protected:
        Monster();

        MonsterModel model = {
        		0, //id
				MonsterType::Blinky,   //type
				MonsterStates::patrol, //state
				MonsterSubStates::move,//sub_state
				200, //pos_x
				200, //pos_y
				200, //prevpos_x
				200, //prev_pos_y
				0, //direction
				0, //target_x
				0, //target_y
				0, //target direction
				0,  //curent_speed
				100, //health
				10, //score_points
				100, //death_score_bonus
				5, //damage_inflicted_per_hit
				10, //damage_suffered_per_hit
				false, //health_gouge_visible
				nullptr //current_animation
        };

    private:

        MonsterSm* mstates[4]={nullptr,nullptr,nullptr,nullptr};
        MonsterView *monster_view;
        QRectF* _sight_box;
        QRectF* _warning_box;

        MonsterStates previus_state;

    };

} //namescpace Monster

#endif // Monster_H
