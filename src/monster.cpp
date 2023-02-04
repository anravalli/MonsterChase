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

#include "monster.h"
#include "monstersm.h"
#include "monsterviews.h"
#include "gameworld.h"
#include "player.h"
#include "arena.h"
#include "animations.h"

#include <assert.h>

namespace Monster{

    Monster *monsterFactory(MonsterType type, QPointF pos){
        static int next_id = 0;

        Monster* monster = new Monster();
        //set moster id
        monster->model.id = next_id;
        next_id++;
        //set position & type
        monster->model.pos_x = pos.x();
        monster->model.pos_y = pos.y();
        monster->model.type = type;
        monster->monster_view = monsterViewFactory(type, &(monster->model));

        //init state machine
        monster->mstates[patrol] = MonsterStateFactory::stateFactory(patrol,type,&(monster->model));
        monster->mstates[attack] =  MonsterStateFactory::stateFactory(attack,type,&(monster->model));
        monster->mstates[flee] =  MonsterStateFactory::stateFactory(flee,type,&(monster->model));
        monster->mstates[dead] =  MonsterStateFactory::stateFactory(dead,type,&(monster->model));

        //default state is "patrol" so let's init the "current_speed" accordingly
        monster->model.curent_speed = monster->mstates[patrol]->move_speed;

        return monster;
    }

    Monster::Monster()
    {
        QApplication::instance()->installEventFilter(this);

        _sight_box = new QRectF(-65, -165, 130, 150);
        _warning_box = new QRectF(-100,-100,200,200);

        monster_view = nullptr;
        previus_state = dead;

    }

    void Monster::addToPage(UiPageViewQt* page)
    {
        monster_view->addToPage(page);
    }

    void Monster::removeFromPage(UiPageViewQt* page)
    {
    	monster_view->removeFromPage(page);
    }

    void Monster::show(){
        monster_view->show();
    }

    void Monster::hide(){
        monster_view->hide();
    }

    void Monster::update(){

        //if(model.health<=0) return;

        // state->enter() is executed at the N+1 step while the exit() is executed
        // inside the N step (when state is changed)
        if(previus_state != model.state){
            mstates[model.state]->enter();
            previus_state = model.state;
        }
        mstates[model.state]->tick();

        monster_view->update();

    }

    int Monster::id(){
        return model.id;
    }

    QRectF Monster::collisionBox() const
    {
        int size = 30;
        return QRectF(model.pos_x-size/2, model.pos_y-size/2,
                      size,size);
    }

    QRectF Monster::sightBox() const
    {
        QTransform t = QTransform().translate(model.pos_x, model.pos_y).rotate(model.direction+90);
        QRectF t_box = t.mapRect(*_sight_box);

        return t_box;
    }

    QRectF Monster::warningBox() const
    {
        QTransform t = QTransform().translate(model.pos_x, model.pos_y);
        QRectF t_box = t.mapRect(*_warning_box);

        return t_box;
    }

    Monster::~Monster(){
        delete mstates[patrol];
        delete mstates[attack];
        delete mstates[flee];
        delete mstates[dead];

        delete _sight_box;
        delete _warning_box;

        delete monster_view;
    }

    int Monster::hit_suffered()
    {
    	static unsigned short cool_down = 0;
    	if (cool_down > 0) {
    		cool_down++;
    		if(cool_down == 13)	cool_down = 0;
    		return 0;
    	}

    	int score_points = model.score_point;
    	model.health -= model.damage_suffered_per_hit;
    	cool_down++;

    	if (model.health <= 0)
    	{
    		model.health = 0;
    		score_points = model.death_score_bonus;
    		model.state = MonsterStates::dead;
    		model.death_score_bonus = 0;
    		model.damage_inflicted_per_hit = 0;
    		qDebug("monster %d is dead", model.id);
    	}
    	qDebug("monster healt is now %d", model.health);
    	return score_points;
    }

	int Monster::hit_inflicted()
	{
		return model.damage_inflicted_per_hit;
	}

	bool Monster::isAlive()
	{
		return not (model.state == MonsterStates::dead and
				model.current_animation->getState() == anim_completed);
	}

} //namescpace Monster
