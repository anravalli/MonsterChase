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

namespace Monster{

    Monster *monsterFactory(MonsterType type, MonsterChase *w, QPointF pos){
        Monster* monster = new Monster(w);
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
        default:
            abort();
            break;
        }

        //init state machine
        monster->mstates[patrol] = MonsterStateFactory::stateFactory(patrol,type,&(monster->model));
        monster->mstates[attack] = new MonsterAttack(&(monster->model));
        monster->mstates[flee] = new MonsterFlee(&(monster->model));

        //adding views to scene
        //the order we add the items to the scene affects the z-order
        monster->addViewComponent(monster->shape);
        monster->addViewComponent(monster->sight);
        return monster;
    }

    Monster::Monster(MonsterChase* w):
        world(w)
    {
        QApplication::instance()->installEventFilter(this);
    }

    void Monster::addViewComponent(QGraphicsItem* component)
    {
        world->getScene()->addItem(component);
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

        checkCollisionsWithPlayer();
        checkCollisionsWithWalls();

        shape->setPos(model.pos_x,model.pos_y);
        shape->setRotation(model.direction);
        sight->setPos(model.pos_x,model.pos_y);
        sight->setRotation(model.direction+90);
        shape->update();
        sight->update();
    }

    void Monster::checkCollisionsWithPlayer(){
        Player* p = world->getPlayer();

        QRectF i = getIntersectonWith(p);
        if (not i.isEmpty()){
            model.sub_state=freeze;
        }
    }

    void Monster::checkCollisionsWithWalls(){
        //model.pos is the center of the collision box
        //getWallsAround needs the top-left and bottom-right corners
        std::vector<Brick*> walls = world->getWallsAround(QPointF(model.pos_x-15,model.pos_y-15),
                                                          QPointF(model.pos_x+15,model.pos_y+15));
        for (auto b: walls){
            QRectF i = collisionBox().intersected(b->boundingRect());
            if (not i.isEmpty()){
                if( 0 == model.direction ){
                    model.pos_x -= i.width();
                }
                else if( 0 < model.direction and model.direction < 90 ){
                    model.pos_x -= i.width();
                    model.pos_y -= i.height();
                }
                else if( 90 == model.direction ){
                    model.pos_y -= i.height();
                }
                else if( 90 < model.direction and model.direction < 180 ){
                    model.pos_x += i.width();
                    model.pos_y -= i.height();
                }
                else if( model.direction == 180 ){
                    model.pos_x += i.width();
                }
                else if( 180 < model.direction and model.direction < 270 ){
                    model.pos_x += i.width();
                    model.pos_y += i.height();
                }
                else if( 270 == model.direction ){
                    model.pos_y += i.height();
                }
                else if( 270 < model.direction and model.direction < 360 ){
                    model.pos_x -= i.width();
                    model.pos_y += i.height();
                }
                else if( 360 == model.direction ){
                    abort();
                }
                else if( 0 > model.direction ){
                    abort();
                }
                model.sub_state=freeze;
            }
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
        //TODO: check wether the QGraphicsItems are deleted by the QGraphicsScene
        // they belongs to
        delete shape;
        delete sight;
    }
    
    MonsterModel *Monster::getModel()
    {
        return &model;
    }
    
    
    
} //namescpace Monster
