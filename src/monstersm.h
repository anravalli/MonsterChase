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

#ifndef MONSTERSM_H
#define MONSTERSM_H

#include "monster.h"
#include "behaviors.h"

class Animation;

namespace Monster{

class MonsterSm;
class MonsterStateFactory
{
public:
    static MonsterSm* stateFactory(MonsterStates state, MonsterType monster, MonsterModel* model);
private:
    static MonsterSm* patrolFactory(MonsterType monster, MonsterModel* model);
    static MonsterSm* attackFactory(MonsterType monster, MonsterModel* model);
    static MonsterSm* fleeFactory(MonsterType monster, MonsterModel* model);
    static MonsterSm* deadFactory(MonsterType monster, MonsterModel* model);
};

class MonsterSm {
public:
    friend class MonsterStateFactory;

    int move_speed = 0;

    virtual void tick() = 0;
    virtual void enter();
    virtual void exit(){}

    virtual ~MonsterSm();
protected:
    MonsterSm(MonsterModel* model);
    MonsterSm* sstates[3]={nullptr,nullptr,nullptr};
    MonsterModel* _model = nullptr;
    Animation *_animation = nullptr;
};

class MonsterPatrol: public MonsterSm {
public:
    MonsterPatrol(MonsterModel* model);

    virtual void tick() override;
    virtual ~MonsterPatrol(){}

private:
protected:
};

class MonsterAttack: public MonsterSm {
public:
    MonsterAttack(MonsterModel* model)
        :MonsterSm(model){}
    virtual void tick() override;
private:
};

class MonsterFlee: public MonsterSm {
public:
    MonsterFlee(MonsterModel* model)
        :MonsterSm(model){}

    virtual void tick() override;
    virtual ~MonsterFlee(){}
private:
};

class MonsterDead: public MonsterSm {
public:
	MonsterDead(MonsterModel* model);

	virtual void enter() override;
	virtual void tick() override {};
	virtual ~MonsterDead();
private:

};

class MonsterPatrolFreeze: public MonsterSm {
public:
    MonsterPatrolFreeze(MonsterModel* model, BasicBehavior *rotate);

    virtual void tick() override;
    void exit() override;

    virtual ~MonsterPatrolFreeze() override;

private:
    BasicBehavior* _rotate;
    BasicBehavior* _player_scanner;
    BasicBehavior* _player_proximity_checker;
    int _freeze_time=25;
    bool _in_position = false;
};

class MonsterPatrolDecide: public MonsterSm {
public:
    MonsterPatrolDecide(MonsterModel* model, BasicBehavior* selector);

    virtual void tick() override;
    virtual ~MonsterPatrolDecide();
protected:
private:
    BasicBehavior* _selector;

};

class MonsterPatrolMove: public MonsterSm {
public:
    MonsterPatrolMove(MonsterModel* model,BasicBehavior *move,BasicBehavior *rotate);

    virtual void tick() override;
    virtual ~MonsterPatrolMove() override;
    void exit() override;

private:
    BasicBehavior* _move;
    BasicBehavior* _walls_checker;
    BasicBehavior* _player_checker;
    BasicBehavior* _player_scanner;
    BasicBehavior* _player_proximity_checker;
    BasicBehavior* _rotate;

    BehaviorStatus _rotation_status = BehaviorStatus::fail;
};

class MonsterAttackFreeze: public MonsterSm {
public:
    MonsterAttackFreeze(MonsterModel* model, BasicBehavior *rotate);

    virtual void tick() override;
    void exit() override;
    virtual ~MonsterAttackFreeze() override;
private:
    BasicBehavior* _rotate;
    BasicBehavior* _player_scanner;
    BasicBehavior* _player_proximity_checker;
    int _freeze_time=10;
    bool _in_position = false;
};

class MonsterAttackDecide: public MonsterSm {
public:
    MonsterAttackDecide(MonsterModel* model, BasicBehavior* selector);

    virtual void tick() override;
    virtual ~MonsterAttackDecide() override {}
protected:
private:
    BasicBehavior* _selector;

};

class MonsterAttackMove: public MonsterSm {
public:
    MonsterAttackMove(MonsterModel* model,BasicBehavior *move,BasicBehavior *rotate);

    virtual void tick() override;
    virtual ~MonsterAttackMove();
private:
    BasicBehavior* _move;
    BasicBehavior* _rotate;

    BasicBehavior* _walls_checker;
    BasicBehavior* _player_checker;
    BasicBehavior* _player_scanner;
    BasicBehavior* _player_proximity_checker;

    BehaviorStatus _rotation_status = BehaviorStatus::fail;
};

class MonsterFleeFreeze: public MonsterSm {
public:
    MonsterFleeFreeze(MonsterModel *model, BasicBehavior *rotate);

    virtual void tick() override;
    void exit() override;
    virtual ~MonsterFleeFreeze() override;
private:
    BasicBehavior* _rotate;
    BasicBehavior* _player_scanner;
    BasicBehavior* _player_proximity_checker;
    int _freeze_time=10;
    bool _in_position = false;
};

class MonsterFleeDecide: public MonsterSm {
public:
    MonsterFleeDecide(MonsterModel* model, BasicBehavior* selector);

    virtual void tick() override;
    virtual ~MonsterFleeDecide() override;
protected:
private:
    BasicBehavior* _selector;

};

class MonsterFleeMove: public MonsterSm {
public:
    MonsterFleeMove(MonsterModel* model,BasicBehavior *move,BasicBehavior *rotate);

    virtual void tick() override;
    virtual ~MonsterFleeMove() override;
private:
    BasicBehavior* _move;
    BasicBehavior* _rotate;

    BasicBehavior* _walls_checker;
    BasicBehavior* _player_checker;
    BasicBehavior* _player_scanner;
    BasicBehavior* _player_proximity_checker;

    BehaviorStatus _rotation_status = BehaviorStatus::fail;
};


}
#endif // MONSTERSM_H
