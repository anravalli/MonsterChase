/*
 *	Monster Chase: a testing playground for behaviors trees
 *
 *	Copyright 2019-2021 Andrea Ravalli <anravalli @ gmail.com>
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


#include "playersm.h"
#include "monster.h"

#include <math.h>

PlayerSm::~PlayerSm(){}

void PlayerSm::moveBy(double step_x, double step_y){
    if(_model->direction[player_up])
        _model->pos_y=_model->pos_y-step_y;
    if(_model->direction[player_down])
        _model->pos_y=_model->pos_y+step_y;
    if(_model->direction[player_left])
        _model->pos_x=_model->pos_x-step_x;
    if(_model->direction[player_right])
        _model->pos_x=_model->pos_x+step_x;
    return;
}

//Player state Normal

PlayerNormal::PlayerNormal(PlayerModel* model) {
    _model=model;
    _max_speed = 3;
    _max_speed_45 = _max_speed/sqrt(2);

}

void PlayerNormal::updateEnergy() {
    _model->energy=_model->energy+0.125;
    if(_model->energy >= MAX_ENERGY){
        _model->energy = MAX_ENERGY;
        _model->state = rage_available;
    }
}

void PlayerNormal::move() {
    double step = _max_speed;
    if((_model->direction[player_up] or _model->direction[player_down])
            and (_model->direction[player_left] or _model->direction[player_right])){
        step = _max_speed_45;
    }
    moveBy(step,step);
}

void PlayerNormal::collisionWithMonster(Monster::Monster *m) {
    _model->energy=_model->energy - m->hit_inflicted();
    if(_model->energy < 0){
        _model->energy = 0;
        _model->state = dead;
    }
    _model->state = on_damage;
}

void PlayerNormal::toggleRage() {}
PlayerNormal::~PlayerNormal(){}

//Player state Rage Available (substate)

void PlayerRageAvailable::toggleRage() {
    _model->state=on_rage;
}

//Player state On Damage (substate)

void PlayerOnDamage::updateEnergy() {
    //PlayerNormal::updateEnergy();
    no_damage_counter--;
    if(no_damage_counter<=0){
        _model->state=normal;
        no_damage_counter=100;
    }
}

//Player state On Rage

PlayerOnRage::PlayerOnRage(PlayerModel* model) {
    _model=model;
    _max_speed = 5;
    _max_speed_45 = _max_speed/sqrt(2);
}

void PlayerOnRage::updateEnergy() {
    _model->energy=_model->energy-0.125;
    if(_model->energy <= DEF_ENERGY)
        _model->state = normal;
}

void PlayerOnRage::move() {
    double step = _max_speed;
    if((_model->direction[player_up] or _model->direction[player_down])
            and (_model->direction[player_left] or _model->direction[player_right])){
        step = _max_speed_45;
    }
    moveBy(step,step);
}
void PlayerOnRage::toggleRage() {
    _model->state=normal;
}
void PlayerOnRage::collisionWithMonster(Monster::Monster *m)  {
	int score_points = m->hit_suffered();
    _model->score=_model->score+score_points;
}

//Player state Dead

PlayerDead::PlayerDead(PlayerModel* model) {
    _model=model;
}

PlayerDead::~PlayerDead() {}
