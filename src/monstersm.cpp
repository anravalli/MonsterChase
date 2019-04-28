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

namespace Monster{

MonsterSm* MonsterStateFactory::stateFactory(MonsterStates state, MonsterType monster, MonsterModel* model)
{
    MonsterSm* new_state = nullptr;
    switch(state){
    case patrol:
        new_state = patrolFactory(monster, model);
        break;
    case attack:
    case flee:
    default:
        abort();
        break;
    }
    return new_state;
}

MonsterSm* MonsterStateFactory::patrolFactory(MonsterType monster, MonsterModel* model)
{
    BasicBehavior* selector = nullptr;
    BasicBehavior* mover = nullptr;
    BasicBehavior* rotator = nullptr;

    MonsterSm* patrol_state = nullptr;

    switch (monster){
    case Blinky:
        selector = new RandomDirection(model);
        mover = new MoveFixedSteps(model, 2, 100);
        rotator = new RandomDirection(model);
        break;
    case Pinky:
    case Inky:
    case Clyde:
        selector = new PerpendicularDirection(model);
        mover = new MoveFixedSteps(model, 4, 100);
        break;
    default:
        abort();
        break;
    }
    patrol_state = new MonsterPatrol(model);
    patrol_state->sstates[MonsterSubStates::route] = new MonsterPatrolDecide(model, selector);
    patrol_state->sstates[MonsterSubStates::move] = new MonsterPatrolMove(model,mover,rotator);
    patrol_state->sstates[MonsterSubStates::freeze] = new MonsterPatrolFreeze(model);
    return  patrol_state;

}

MonsterPatrol::MonsterPatrol(MonsterModel *model)
    :_model(model)
{
     _model->sub_state = MonsterSubStates::route;
}

void MonsterPatrol::tick(){
    sstates[_model->sub_state]->tick();
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
//    _model->pos_x=_model->pos_x-_speed;
//    _model->pos_x=_model->pos_x+_speed;
    return;
}

void MonsterPatrolFreeze::tick(){
    if( (_freeze_time > 0) ){
//        if(_model->target_direction > _model->direction) {
//            _model->direction = _model->direction >= 360 ? 0 : _model->direction+10;
//        }
//        else if(_model->target_direction < _model->direction) {
//                _model->direction = _model->direction-10;
//        }
        _freeze_time--;
    }
    else{
        _freeze_time=10;
        _model->sub_state=MonsterSubStates::route;
    }
}

MonsterPatrolDecide::MonsterPatrolDecide(MonsterModel *model, BasicBehavior *selector)
    :_model(model), _selector(selector)
{
}

void MonsterPatrolDecide::tick()
{
    _selector->exec(); //_model->direction updated by selector

    _model->sub_state = MonsterSubStates::move;
    return;
}

void MonsterPatrolMove::tick(){

    if (BehaviorStatus::running != _move->exec())
        _model->sub_state = MonsterSubStates::route;


//    if( _model->target_direction > _model->direction ) {
//        _model->direction += 2;
//    }
//    else
//        _model->direction -= 2;
}

}
