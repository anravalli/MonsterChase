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

#include "monstersm.h"
#include <math.h>       /* cos */

#define PI 3.14159265

namespace Monster{

MonsterPatrol::MonsterPatrol(MonsterModel *model)
    :_model(model)
{
    //;
    mstates[MonsterSubStates::route] = new MonsterPatrolDecide(_model);
    mstates[MonsterSubStates::move] = new MonsterPatrolMove(_model);
    mstates[MonsterSubStates::freeze] = new MonsterPatrolFreeze(_model);

    _model->sub_state = MonsterSubStates::route;
}

void MonsterPatrol::tick(){
    mstates[_model->sub_state]->tick();
}

void MonsterAttack::tick(){
    move();
}

void MonsterAttack::move(){
    return;
}

void MonsterFlee::tick(){
    move();
}

void MonsterFlee::move(){
    _model->pos_x=_model->pos_x-_speed;
    _model->pos_x=_model->pos_x+_speed;
    return;
}

void MonsterPatrolFreeze::tick(){
    if( (_freeze_time > 0) or (_model->target_direction > _model->direction) ) {
        _freeze_time--;
        _model->direction = _model->direction >= 360 ? 0 : _model->direction+10;
    }
    else{
        _freeze_time=10;
        _model->sub_state=MonsterSubStates::route;
    }
}

MonsterPatrolDecide::MonsterPatrolDecide(MonsterModel *model)
    :_model(model)
{
    switch(_model->type){
    case Blinky:
        selector = new RandomDirection(_model);
        break;
    case Pinky:
    case Inky:
    case Clyde:
        selector = new PerpendicularDirection(_model);
        break;
    default:
        exit(5);
        break;
    }
}

void MonsterPatrolDecide::tick()
{
    selector->exec(); //_model->direction updated by selector

    _model->sub_state = MonsterSubStates::move;
    return;
}

void MonsterPatrolMove::tick(){

    if (_steps < 100){
        double dx = cos ( _model->direction * PI / 180.0 ) * _speed;
        double dy = sin( _model->direction * PI / 180.0 ) * _speed;
        _model->pos_x += dx;
        _model->pos_y += dy;
        _steps++;
    }
    else {
        _steps = 0;
        _model->sub_state = MonsterSubStates::route;
    }

    if( _model->target_direction > _model->direction ) {
        _model->direction += 2;
    }
}

}
