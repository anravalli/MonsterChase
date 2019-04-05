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

namespace Monster{

    Monster::Monster(MonsterChase* w):
        world(w)
    {

        shape = new MonsterShape(&model);
        sight = new MonsterSight(&model);

        //init state machine
        mstates[patrol] = new MonsterPatrol(&model);
        mstates[attack] = new MonsterAttack(&model);
        mstates[flee] = new MonsterFlee(&model);
        mstates[freeze] = new MonsterFreeze(&model);

        //the order we add the items to the scene affects the z-order
        world->getScene()->addItem(shape);
        world->getScene()->addItem(sight);

        QApplication::instance()->installEventFilter(this);
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

        checkCollisionsWithPlayer();

        shape->setPos(model.pos_x,model.pos_y);
        shape->setRotation(model.direction);
        sight->setPos(model.pos_x,model.pos_y);
        sight->setRotation(model.direction);
        shape->update();
        sight->update();
    }

    void Monster::checkCollisionsWithPlayer(){
        //MonsterSm* cstate = mstates[model.state];
        Player* p = world->getPlayer();

        QRectF i = getIntersectonWith(p);
        if (not i.isEmpty()){
            model.state=freeze;
            //p->collisionWithMonster();
        }
    }

    QRectF Monster::getIntersectonWith(Player* p)
    {
        QRectF mb = p->collisionBox();
        return collisionBox().intersected(mb);
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
        delete mstates[freeze];
        //TODO: check wether the QGraphicsItems are deleted by the QGraphicsScene
        // they belongs to
        delete shape;
        delete sight;
    }



} //namescpace Monster
