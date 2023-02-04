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

#include <ui_framework/uipageview_qt.h>
#include "player.h"
#include "playersm.h"
#include "playerqtviews.h"
#include "gameworld.h"
#include "monster.h"
#include "arena.h"
#include "animations.h"

#include "algorithms.h"

Player::Player()
{

    shape = new PlayerShape(&model);
    energy_gauge = new PlayerEnergyGauge(&model);
    score = new PlayerScore(&model);

    //init state machine
    pstates[normal] = new PlayerNormal(&model);
    pstates[rage_available] = new PlayerRageAvailable(&model);
    pstates[on_rage] = new PlayerOnRage(&model);
    pstates[on_damage] = new PlayerOnDamage(&model);
    pstates[dead] = new PlayerDead(&model);

    pstates[current_state]->enter();
}

void Player::show(){
    shape->show();
}
void Player::hide(){
    shape->hide();
}

void Player::addToPage(UiPageViewQt* page)
{
    page->addItem(this->shape);
    page->addItem(this->score);
    page->addItem(this->energy_gauge);
}

void Player::removeFromPage(UiPageViewQt* page)
{
    page->removeItem(this->shape);
    page->removeItem(this->score);
    page->removeItem(this->energy_gauge);
}

void Player::setEnergyGaugePos(int x, int y){
    x = x - energy_gauge->boundingRect().width()/2;
    energy_gauge->setPos(x,y);
}

void Player::update(){
    computeState();

    checkCollisionsWithWalls();
    checkCollisionsWithMonsters();

    updateViews();

#ifdef  DEBUG
    qDebug("Player energy %d", model.energy);
#endif
}

void Player::computeState(){
	PlayerSm* cstate = pstates[model.state];
	if(current_state != model.state){
		pstates[current_state]->exit();
		cstate->enter();
	}

    cstate->updateEnergy();
    cstate->move();
    model.current_animation->update();
}

void Player::collisionWithMonster(Monster::Monster *m){
    PlayerSm* cstate = pstates[model.state];
    cstate->collisionWithMonster(m);
}

void Player::checkCollisionsWithMonsters(){
    PlayerSm* cstate = pstates[model.state];
    std::vector<Monster::Monster*> monsters = GameWorld::instance().getMonsters();
    for (auto m: monsters){
        QRectF i = getIntersectonWith(m);
        if (not i.isEmpty()){
            double step = i.width();
            if(i.height()<i.width())
                step = i.height();
            cstate->moveBy(-step,-step);
            cstate->collisionWithMonster(m);
        }
    }

}

void Player::checkCollisionsWithWalls(){
    PlayerSm* cstate = pstates[model.state];
    //model.pos is the center of the collision box
    //getWallsAround needs the top-left and bottom-right corners
    std::vector<Brick*> walls = GameWorld::instance().getWallsAround(QPointF(model.pos_x-15,model.pos_y-15),
                                                      QPointF(model.pos_x+15,model.pos_y+15));
    for (auto b: walls){
        QRectF i = collisionBox().intersected(b->boundingRect());
        if (not i.isEmpty()){
            double step = i.width();
            if(i.height()<i.width())
                step = i.height();
            cstate->moveBy(-step,-step);
        }
    }

}

void Player::updateViews(){
    energy_gauge->update();
    shape->setPos(model.pos_x,model.pos_y);
    shape->update();
    score->updateScore();
}

QRectF Player::getIntersectonWith(Monster::Monster* m)
{
    QRectF mb = m->collisionBox();
    return collisionBox().intersected(mb);
}

QRectF Player::collisionBox() const
{
    int size = 30;
    return QRectF(model.pos_x-size/2, model.pos_y-size/2,
                  size,size);
}

bool Player::handleKey(int key, bool released){
    bool ret = false;

    switch(key){
    case Qt::Key_Space:
#ifdef  DEBUG
        qDebug("--> Handling Spacebar");
#endif
        if(!released)pstates[model.state]->toggleRage();
        ret = true;
        break;
    case Qt::Key_D:
    case Qt::Key_Right:
        model.direction[player_right]=!released;
        break;
    case Qt::Key_A:
    case Qt::Key_Left:
        model.direction[player_left]=!released;
        break;
    case Qt::Key_Up:
    case Qt::Key_W:
        model.direction[player_up]=!released;
        break;
    case Qt::Key_S:
    case Qt::Key_Down:
        model.direction[player_down]=!released;
        break;
    default:
        break;
    }
    return ret;
}

void Player::setScorePos(int x, int y){
    score->setPos(x,y);
}

PlayerEnergyGauge *Player::getEnergyGauge(){
    return energy_gauge;
}

PlayerStates Player::getRageStatus(){
    return model.state;
}

Player::~Player(){
    delete pstates[normal];
    delete pstates[rage_available];
    delete pstates[on_damage];
    delete pstates[on_rage];
    delete pstates[dead];
    //TODO: check wether the QGraphicsItems are deleted by the QGraphicsScene
    // they belongs to
    delete shape;
    delete energy_gauge;
}
