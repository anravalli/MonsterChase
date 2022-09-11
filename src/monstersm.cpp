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
#include "gameworld.h"
#include "player.h"

namespace Monster{

MonsterSm::~MonsterSm()
{

}

void MonsterSm::enter()
{
    this->_model->curent_speed = this->move_speed;
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

    MonsterSm* patrol_state = new MonsterPatrol(model);

    switch (monster){
    case Blinky:
        selector = new RandomDirection(model);
        mover = new MoveFixedSteps(model, 2, 100);
        rotator = new LinearRotation(model, 3);
        freeze_rotator = new LinearRotation(model, 5);
        patrol_state->move_speed = 2;
        break;
    case Pinky:
    case Inky:
    case Clyde:
        selector = new PerpendicularDirection(model);
        mover = new MoveFixedSteps(model, 4, 100);
        rotator = new TronRotation(model);
        freeze_rotator = rotator;
        patrol_state->move_speed = 4;
        break;
    }
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

    MonsterSm* attack_state = new MonsterPatrol(model);

    switch (monster){
    case Blinky:
        selector = new RandomDirection(model);
        mover = new MoveToTarget(model, 4);
        rotator = new LinearRotation(model, 5);
        freeze_rotator = new TronRotation(model);
        attack_state->move_speed = 4;
        break;
    case Pinky:
    case Inky:
    case Clyde:
        selector = new PerpendicularDirection(model);
        mover = new MoveToTarget(model, 6);
        rotator = new TronRotation(model);
        freeze_rotator = rotator;
        attack_state->move_speed = 6;
        break;
    }
    attack_state->sstates[MonsterSubStates::route] = new MonsterPatrolDecide(model, selector);
    attack_state->sstates[MonsterSubStates::move] = new MonsterAttackMove(model,mover,rotator);
    attack_state->sstates[MonsterSubStates::freeze] = new MonsterAttackFreeze(model,freeze_rotator);
    return  attack_state;

}

MonsterSm* MonsterStateFactory::fleeFactory(MonsterType monster, MonsterModel* model)
{
    BasicBehavior* selector = nullptr;
    BasicBehavior* mover = nullptr;
    BasicBehavior* rotator = nullptr;
    BasicBehavior* freeze_rotator = nullptr;

    MonsterSm* flee_state = new MonsterPatrol(model);

    switch (monster){
    case Blinky:
        selector = new RandomDirection(model);
        mover = new MoveToTarget(model, 4);
        rotator = new LinearRotation(model, 5);
        freeze_rotator = new TronRotation(model);
        flee_state->move_speed = 4;
        break;
    case Pinky:
    case Inky:
    case Clyde:
        selector = new PerpendicularDirection(model);
        mover = new MoveToTarget(model, 6);
        rotator = new TronRotation(model);
        freeze_rotator = rotator;
        flee_state->move_speed = 6;
        break;
    }
    flee_state->sstates[MonsterSubStates::route] = new MonsterPatrolDecide(model, selector);
    flee_state->sstates[MonsterSubStates::move] = new MonsterFleeMove(model,mover,rotator);
    flee_state->sstates[MonsterSubStates::freeze] = new MonsterFleeFreeze(model,freeze_rotator);
    return  flee_state;

}

/*
 * Monster Patrol State
 */
MonsterPatrol::MonsterPatrol(MonsterModel *model)
    :MonsterSm(model)
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
MonsterPatrolFreeze::MonsterPatrolFreeze(MonsterModel *model, BasicBehavior *rotate)
    :MonsterSm(model), _rotate(rotate){
    int monster_size = 30;
    _player_scanner = new PlayerAtSightChecker(model, monster_size);
    _player_proximity_checker = new PlayerProximityChecker(model, monster_size);
}

void MonsterPatrolFreeze::tick(){

	_model->health_gouge_visible = false;

    _in_position = (BehaviorStatus::running != _rotate->exec());

    if (BehaviorStatus::success == _player_scanner->exec()){
    	_model->health_gouge_visible = true;
        if(GameWorld::instance().getPlayer()->getRageStatus() == PlayerStates::on_rage)
            _model->state=flee;
        else
            _model->state=attack;
        exit();
    }

	if (BehaviorStatus::success == _player_proximity_checker->exec()){
		_model->health_gouge_visible |= true;
		if(GameWorld::instance().getPlayer()->getRageStatus() == PlayerStates::on_rage){
			_model->state=flee;
			exit();
		}
	}

    if( (_freeze_time <= 0 and _in_position) ){
        _freeze_time=25;
        _model->sub_state=MonsterSubStates::route;
        exit();
    }
    else if(_freeze_time > 0)
        _freeze_time--;

    return;
}

void MonsterPatrolFreeze::exit() {
    _in_position = false;
}

MonsterPatrolFreeze::~MonsterPatrolFreeze() {
    delete _player_scanner;
    delete _rotate;
}

MonsterPatrolDecide::MonsterPatrolDecide(MonsterModel *model, BasicBehavior *selector)
    : MonsterSm(model), _selector(selector)
{
}

void MonsterPatrolDecide::tick()
{
    _selector->exec(); //_model->direction updated by selector

    _model->sub_state = MonsterSubStates::move;
    return;
}

MonsterPatrolDecide::~MonsterPatrolDecide(){
    delete _selector;
}

MonsterPatrolMove::MonsterPatrolMove(MonsterModel *model, BasicBehavior *move, BasicBehavior *rotate)
    :MonsterSm(model),_move(move),_rotate(rotate)
{
    int monster_size = 30; //temporary harcoded
    _walls_checker = new WallsCollisionChecker(model, monster_size);
    _player_checker = new EntitiesCollisionChecker(model, monster_size);
    _player_scanner = new PlayerAtSightChecker(model, monster_size);
    _player_proximity_checker = new PlayerProximityChecker(model, monster_size);
}

void MonsterPatrolMove::tick(){
	_model->health_gouge_visible = false;

    if (BehaviorStatus::running != _move->exec()){
        _model->sub_state = MonsterSubStates::route;
        exit();
    }

    if (BehaviorStatus::success == _walls_checker->exec()){
        _model->sub_state=MonsterSubStates::freeze;
        exit();
    }
    if (BehaviorStatus::success == _player_checker->exec()){
        _model->sub_state=MonsterSubStates::freeze;
        exit();
    }

    if (BehaviorStatus::success == _player_scanner->exec()){
    	_model->health_gouge_visible = true;
        if(GameWorld::instance().getPlayer()->getRageStatus() == PlayerStates::on_rage){
            _model->state=MonsterStates::flee;
            _model->sub_state = MonsterSubStates::route;
        }
        else
            _model->state=MonsterStates::attack;
        exit();
    }

    if (BehaviorStatus::success == _player_proximity_checker->exec()){
    	_model->health_gouge_visible |= true;

    	if(GameWorld::instance().getPlayer()->getRageStatus() == PlayerStates::on_rage){
    		_model->state=MonsterStates::flee;
    		_model->sub_state = MonsterSubStates::route;
    		exit();
    	}
    }

    if (BehaviorStatus::success != _rotation_status)
        _rotation_status = _rotate->exec();


    return;
}

MonsterPatrolMove::~MonsterPatrolMove() {
    delete _move;
    delete _walls_checker;
    delete _player_checker;
    delete _player_scanner;
    delete _player_proximity_checker;
    delete _rotate;
}

void MonsterPatrolMove::exit() {
    _rotation_status = BehaviorStatus::fail;
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
MonsterAttackMove::MonsterAttackMove(MonsterModel *model, BasicBehavior *move, BasicBehavior *rotate)
    :MonsterSm(model),_move(move),_rotate(rotate)
{
    int monster_size = 30; //temporary harcoded
    _walls_checker = new WallsCollisionChecker(model, monster_size);
    _player_checker = new EntitiesCollisionChecker(model, monster_size);
    _player_scanner = new PlayerAtSightChecker(model, monster_size);
    _player_proximity_checker = new PlayerProximityChecker(model, monster_size);
}

//REMINDER :no state exit implemented even if used
//NOTE: rotation is aborted in Patrol state
void MonsterAttackMove::tick(){
	//reset energy gouge visibility: it will be set later by behaviors
	_model->health_gouge_visible = false;

    if (BehaviorStatus::running != _move->exec()){
        _model->sub_state = MonsterSubStates::route;
        exit();
    }

    if (BehaviorStatus::success == _walls_checker->exec()){
        _model->sub_state=MonsterSubStates::freeze;
        exit();
    }

    if (BehaviorStatus::success == _player_checker->exec()){
        _model->sub_state=MonsterSubStates::freeze;
        exit();
    }

    if (BehaviorStatus::success == _player_scanner->exec()){
    	_model->health_gouge_visible = true;

    	if(GameWorld::instance().getPlayer()->getRageStatus() == PlayerStates::on_rage) {
    		_model->state=MonsterStates::flee;
    		_model->sub_state = MonsterSubStates::route;
    		exit();
    	}
    }
    else{
    	_model->state=MonsterStates::patrol;
    	exit();
    }

    if (BehaviorStatus::success == _player_proximity_checker->exec()){
    	_model->health_gouge_visible |= true;

    	if(GameWorld::instance().getPlayer()->getRageStatus() == PlayerStates::on_rage){
    		_model->state=MonsterStates::flee;
    		_model->sub_state = MonsterSubStates::route;
    		exit();
    	}
    }

    if (BehaviorStatus::success != _rotation_status)
        _rotation_status = _rotate->exec();

    return;
}

MonsterAttackMove::~MonsterAttackMove(){
    delete _move;
    delete _walls_checker;
    delete _player_checker;
    delete _player_scanner;
    delete _player_proximity_checker;
    delete _rotate;
}

void MonsterAttackDecide::tick(){
    return;
}

MonsterAttackFreeze::MonsterAttackFreeze(MonsterModel *model, BasicBehavior *rotate)
    :MonsterSm(model), _rotate(rotate){
    int monster_size = 30;
    _player_scanner = new PlayerAtSightChecker(model, monster_size);
    _player_proximity_checker = new PlayerProximityChecker(model, monster_size);
}

void MonsterAttackFreeze::tick(){
	_model->health_gouge_visible = false;

    _in_position = (BehaviorStatus::running != _rotate->exec());

    if (BehaviorStatus::success == _player_scanner->exec()){
    	_model->health_gouge_visible = true;

    	if(GameWorld::instance().getPlayer()->getRageStatus() == PlayerStates::on_rage) {
    		_model->state=MonsterStates::flee;
    		_model->sub_state = MonsterSubStates::route;
    		exit();
    	}
    }
    else{
    	_model->state=MonsterStates::patrol;
    	exit();
    }

    if (BehaviorStatus::success == _player_proximity_checker->exec()){
    	_model->health_gouge_visible |= true;

    	if(GameWorld::instance().getPlayer()->getRageStatus() == PlayerStates::on_rage){
    		_model->state=MonsterStates::flee;
    		_model->sub_state = MonsterSubStates::route;
    		exit();
    	}
    }

    if( (_freeze_time <= 0 and _in_position) ){
        _freeze_time=25;
        _model->sub_state=MonsterSubStates::route;
        exit();
    }
    else if(_freeze_time > 0)
        _freeze_time--;

    return;
}

void MonsterAttackFreeze::exit() {
    _in_position = false;
}

MonsterAttackFreeze::~MonsterAttackFreeze(){
    delete _player_scanner;
    delete _rotate;
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
MonsterFleeMove::MonsterFleeMove(MonsterModel *model, BasicBehavior *move, BasicBehavior *rotate)
    :MonsterSm(model),_move(move),_rotate(rotate){
    int monster_size = 30; //temporary harcoded
    _walls_checker = new WallsCollisionChecker(model, monster_size);
    _player_checker = new EntitiesCollisionChecker(model, monster_size);
    _player_proximity_checker = new PlayerProximityChecker(model, monster_size);
}

//REMINDER: no state exit() implemented even if used
//NOTE: rotation is aborted in Patrol state
void MonsterFleeMove::tick(){

	_model->health_gouge_visible = true;

    if (BehaviorStatus::running != _move->exec()){
        _model->sub_state = MonsterSubStates::route;
        exit();
    }

    //TODO: need to find a better way to set event priority
    if(GameWorld::instance().getPlayer()->getRageStatus() != PlayerStates::on_rage) {
        _model->state=MonsterStates::patrol;
        exit();
    }

    if (BehaviorStatus::success == _walls_checker->exec()){
        _model->sub_state=MonsterSubStates::freeze;
        exit();
    }
    if (BehaviorStatus::success == _player_checker->exec()){
        _model->sub_state=MonsterSubStates::freeze;
        exit();
    }

    if (BehaviorStatus::success != _rotation_status)
        _rotation_status = _rotate->exec();
    return;
}

MonsterFleeMove::~MonsterFleeMove() {
    delete _move;
    delete _walls_checker;
    delete _player_checker;
    delete _player_proximity_checker;
    delete _rotate;
}

MonsterFleeDecide::MonsterFleeDecide(MonsterModel *model, BasicBehavior *selector)
    :MonsterSm(model), _selector(selector)
{
}

void MonsterFleeDecide::tick(){

    _model->sub_state = MonsterSubStates::move;
    return;
}

MonsterFleeDecide::~MonsterFleeDecide() {
    delete _selector;
}

MonsterFleeFreeze::MonsterFleeFreeze(MonsterModel *model, BasicBehavior *rotate)
    :MonsterSm(model), _rotate(rotate){
    int monster_size = 30;
    _player_scanner = new PlayerAtSightChecker(model, monster_size);
    _player_proximity_checker = new PlayerProximityChecker(model, monster_size);
}

void MonsterFleeFreeze::tick(){
	_model->health_gouge_visible = false;

	_in_position = (BehaviorStatus::running != _rotate->exec());

	if (BehaviorStatus::success == _player_proximity_checker->exec()){
		_model->health_gouge_visible = true;
		if(GameWorld::instance().getPlayer()->getRageStatus() != PlayerStates::on_rage){
			_model->state=MonsterStates::patrol;
			exit();
		}
	}

	if (BehaviorStatus::success == _player_scanner->exec()){
		_model->health_gouge_visible |= true;
		if(GameWorld::instance().getPlayer()->getRageStatus() == PlayerStates::on_rage){
			_model->state=MonsterStates::flee;
			_model->sub_state = MonsterSubStates::route;
		}
		else
			_model->state=MonsterStates::attack;
		exit();
	}

	if( (_freeze_time <= 0 and _in_position) ){
		_freeze_time=25;
		_model->sub_state=MonsterSubStates::route;
		exit();
	}
	else if(_freeze_time > 0)
		_freeze_time--;

	return;
}

void MonsterFleeFreeze::exit() {
    _in_position = false;
}

MonsterFleeFreeze::~MonsterFleeFreeze() {
    delete _player_proximity_checker;
    delete _rotate;
}

}
