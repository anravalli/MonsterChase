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

MonsterSm::~MonsterSm()
{

}

/*
 * State Factory
 */
MonsterSm* MonsterStateFactory::stateFactory(MonsterStates state, MonsterType monster, MonsterModel* model)
{
    MonsterSm* new_state = nullptr;
    switch(state){
    case patrol:
        new_state = patrolFactory(monster, model);
        break;
    case attack:
        new_state = attackFactory(monster, model);
        break;
    case flee:
        new_state = fleeFactory(monster, model);
        break;
    }
    return new_state;
}

MonsterSm* MonsterStateFactory::patrolFactory(MonsterType monster, MonsterModel* model)
{
    BasicBehavior* selector = nullptr;
    BasicBehavior* mover = nullptr;
    BasicBehavior* rotator = nullptr;
    BasicBehavior* freeze_rotator = nullptr;

    MonsterSm* patrol_state = nullptr;

    switch (monster){
    case Blinky:
        selector = new RandomDirection(model);
        mover = new MoveFixedSteps(model, 2, 100);
        rotator = new LinearRotation(model, 2);
        freeze_rotator = new TronRotation(model);
        break;
    case Pinky:
    case Inky:
    case Clyde:
        selector = new PerpendicularDirection(model);
        mover = new MoveFixedSteps(model, 4, 100);
        rotator = new TronRotation(model);
        freeze_rotator = rotator;
        break;
    }
    patrol_state = new MonsterPatrol(model);
    patrol_state->sstates[MonsterSubStates::route] = new MonsterPatrolDecide(model, selector);
    patrol_state->sstates[MonsterSubStates::move] = new MonsterPatrolMove(model,mover,rotator);
    patrol_state->sstates[MonsterSubStates::freeze] = new MonsterPatrolFreeze(model,freeze_rotator);
    return  patrol_state;

}

MonsterSm* MonsterStateFactory::attackFactory(MonsterType monster, MonsterModel* model)
{
    BasicBehavior* selector = nullptr;
    BasicBehavior* mover = nullptr;
    BasicBehavior* rotator = nullptr;
    BasicBehavior* freeze_rotator = nullptr;

    MonsterSm* attack_state = nullptr;

    switch (monster){
    case Blinky:
        selector = new RandomDirection(model);
        mover = new MoveFixedSteps(model, 2, 100);
        rotator = new LinearRotation(model, 2);
        freeze_rotator = new TronRotation(model);
        break;
    case Pinky:
    case Inky:
    case Clyde:
        selector = new PerpendicularDirection(model);
        mover = new MoveFixedSteps(model, 4, 100);
        rotator = new TronRotation(model);
        freeze_rotator = rotator;
        break;
    }
    attack_state = new MonsterPatrol(model);
    attack_state->sstates[MonsterSubStates::route] = new MonsterPatrolDecide(model, selector);
    attack_state->sstates[MonsterSubStates::move] = new MonsterPatrolMove(model,mover,rotator);
    attack_state->sstates[MonsterSubStates::freeze] = new MonsterPatrolFreeze(model,freeze_rotator);
    return  attack_state;

}

MonsterSm* MonsterStateFactory::fleeFactory(MonsterType monster, MonsterModel* model)
{
    BasicBehavior* selector = nullptr;
    BasicBehavior* mover = nullptr;
    BasicBehavior* rotator = nullptr;
    BasicBehavior* freeze_rotator = nullptr;

    MonsterSm* flee_state = nullptr;

    switch (monster){
    case Blinky:
    case Pinky:
    case Inky:
    case Clyde:
        break;
    }
    flee_state = new MonsterPatrol(model);
    flee_state->sstates[MonsterSubStates::route] = new MonsterPatrolDecide(model, selector);
    flee_state->sstates[MonsterSubStates::move] = new MonsterPatrolMove(model,mover,rotator);
    flee_state->sstates[MonsterSubStates::freeze] = new MonsterPatrolFreeze(model,freeze_rotator);
    return  flee_state;

}

/*
 * Monster Patrol State
 */
MonsterPatrol::MonsterPatrol(MonsterModel *model)
    :_model(model)
{
     _model->sub_state = MonsterSubStates::route;
     return;
}

void MonsterPatrol::tick(){
    sstates[_model->sub_state]->tick();
    return;
}

/*
 * Monster Patrol Sub State
 */
void MonsterPatrolFreeze::tick(){
    if( (_freeze_time > 0) ){
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

    if (BehaviorStatus::running != _move->exec()){
        _model->sub_state = MonsterSubStates::route;
        _rotation_status = BehaviorStatus::fail;
    }

//    if (BehaviorStatus::success != _rotation_status)
//        _rotation_status = _rotate->exec();

    return;
}

/*
 * Monster Attack State
 */
void MonsterAttack::tick(){
    sstates[_model->sub_state]->tick();
    return;
}

/*
 * Monster Attack Sub State
 */
void MonsterAttackMove::tick(){
    return;
}

void MonsterAttackDecide::tick(){
    return;
}

void MonsterAttackFreeze::tick(){
    return;
}

/*
 * Monster Flee State
 */
void MonsterFlee::tick(){
    sstates[_model->sub_state]->tick();
    return;
}

/*
 * Monster Flee Sub State
 */
void MonsterFleeMove::tick(){
    return;
}

void MonsterFleeDecide::tick(){
    return;
}

void MonsterFleeFreeze::tick(){
    return;
}

}
