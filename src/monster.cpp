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
#include "monsterchase.h"
#include "player.h"
#include "arena.h"

#include <assert.h>

namespace Monster{

    Monster *monsterFactory(MonsterType type, QPointF pos){
        Monster* monster = new Monster();
        //set position & type
        monster->model.pos_x = pos.x();
        monster->model.pos_y = pos.y();
        monster->model.type = type;

        //type related elements
        switch (type){
        case Blinky:
            //set shapes
            monster->shape = new MonsterShape(&(monster->model));
            monster->sight = new MonsterSight(&(monster->model));
            break;
        case Pinky:
            //set shapes
            monster->shape = new MonsterTriangularShape(&(monster->model));
            monster->sight = new MonsterSight(&(monster->model));
            break;
        case Inky:
            //set shapes
            monster->shape = new MonsterShape(&(monster->model));
            monster->sight = new MonsterSight(&(monster->model));
            break;
        case Clyde:
            //set shapes
            monster->shape = new MonsterTriangularShape(&(monster->model));
            monster->sight = new MonsterSight(&(monster->model));
            break;
        }

        //init state machine
        monster->mstates[patrol] = MonsterStateFactory::stateFactory(patrol,type,&(monster->model));
        monster->mstates[attack] =  MonsterStateFactory::stateFactory(attack,type,&(monster->model));
        monster->mstates[flee] =  MonsterStateFactory::stateFactory(flee,type,&(monster->model));

        //adding views to scene
        //the order we add the items to the scene affects the z-order
        monster->addViewComponent(monster->shape);
        monster->addViewComponent(monster->sight);
        return monster;
    }

    Monster::Monster()
    {
        QApplication::instance()->installEventFilter(this);
    }

    void Monster::addViewComponent(QGraphicsItem* component)
    {
        MonsterChase::instance().getScene()->addItem(component);
        return;
    }

    void Monster::show(){
        shape->show();
        sight->show();
    }

    void Monster::hide(){
        shape->hide();
        sight->hide();
    }

    void Monster::update(){
        mstates[model.state]->tick();

        shape->setPos(model.pos_x,model.pos_y);
        shape->setRotation(model.direction);
        sight->setPos(model.pos_x,model.pos_y);
        sight->setRotation(model.direction+90);
        shape->update();
        sight->update();
    }

    QRectF Monster::collisionBox() const
    {
        int size = 30;
        return QRectF(model.pos_x-size/2, model.pos_y-size/2,
                      size,size);
    }

    Monster::~Monster(){
        delete mstates[patrol];
        delete mstates[attack];
        delete mstates[flee];
        //TODO: check wether the QGraphicsItems are deleted by the QGraphicsScene
        // they belongs to
        delete shape;
        delete sight;
    }

} //namescpace Monster
