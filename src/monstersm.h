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
};

class MonsterSm {
public:
    friend class MonsterStateFactory;

    virtual void tick() = 0;
    virtual ~MonsterSm(){}
protected:
    MonsterSm* sstates[3]={nullptr,nullptr,nullptr};
};

class MonsterPatrol: public MonsterSm {
public:
    MonsterPatrol(MonsterModel* model);

    virtual void tick();
    virtual ~MonsterPatrol(){}

private:
protected:
    MonsterModel* _model;

    void move();
};

class MonsterAttack: public MonsterSm {
public:
    MonsterAttack(MonsterModel* model)
        :_model(model){}
    virtual void tick();
private:
    MonsterModel* _model;

    void move();
};

class MonsterFlee: public MonsterSm {
public:
    MonsterFlee(MonsterModel* model)
        :_model(model){}

    virtual void tick();
    virtual ~MonsterFlee(){}
private:
    MonsterModel* _model;
    //int _speed=10;

    void move();
};

class MonsterPatrolFreeze: public MonsterSm {
public:
    MonsterPatrolFreeze(MonsterModel* model, BasicBehavior *rotate)
        :_model(model), _rotate(rotate){}

    virtual void tick();
    virtual ~MonsterPatrolFreeze(){}
private:
    MonsterModel* _model;
    BasicBehavior* _rotate;
    int _freeze_time=10;
};

class MonsterPatrolDecide: public MonsterSm {
public:
    MonsterPatrolDecide(MonsterModel* model, BasicBehavior* selector);

    virtual void tick();
    virtual ~MonsterPatrolDecide(){}
protected:
private:
    MonsterModel* _model;
    BasicBehavior* _selector;

};

class MonsterPatrolMove: public MonsterSm {
public:
    MonsterPatrolMove(MonsterModel* model,BasicBehavior *move,BasicBehavior *rotate)
        :_model(model),_move(move),_rotate(rotate){}

    virtual void tick();
    virtual ~MonsterPatrolMove(){}
private:
    MonsterModel* _model;
    BasicBehavior* _move;
    BasicBehavior* _rotate;

    BehaviorStatus _rotation_status = BehaviorStatus::fail;
};

class MonsterAttackFreeze: public MonsterSm {
public:
    MonsterAttackFreeze(MonsterModel* model, BasicBehavior *rotate)
        :_model(model), _rotate(rotate){}

    virtual void tick();
    virtual ~MonsterAttackFreeze(){}
private:
    MonsterModel* _model;
    BasicBehavior* _rotate;
    int _freeze_time=10;
};

class MonsterAttackDecide: public MonsterSm {
public:
    MonsterAttackDecide(MonsterModel* model, BasicBehavior* selector);

    virtual void tick();
    virtual ~MonsterAttackDecide(){}
protected:
private:
    MonsterModel* _model;
    BasicBehavior* _selector;

};

class MonsterAttackMove: public MonsterSm {
public:
    MonsterAttackMove(MonsterModel* model,BasicBehavior *move,BasicBehavior *rotate)
        :_model(model),_move(move),_rotate(rotate){}

    virtual void tick();
    virtual ~MonsterAttackMove(){}
private:
    MonsterModel* _model;
    BasicBehavior* _move;
    BasicBehavior* _rotate;

    BehaviorStatus _rotation_status = BehaviorStatus::fail;
};

class MonsterFleeFreeze: public MonsterSm {
public:
    MonsterFleeFreeze(MonsterModel* model, BasicBehavior *rotate)
        :_model(model), _rotate(rotate){}

    virtual void tick();
    virtual ~MonsterFleeFreeze(){}
private:
    MonsterModel* _model;
    BasicBehavior* _rotate;
    int _freeze_time=10;
};

class MonsterFleeDecide: public MonsterSm {
public:
    MonsterFleeDecide(MonsterModel* model, BasicBehavior* selector);

    virtual void tick();
    virtual ~MonsterFleeDecide(){}
protected:
private:
    MonsterModel* _model;
    BasicBehavior* _selector;

};

class MonsterFleeMove: public MonsterSm {
public:
    MonsterFleeMove(MonsterModel* model,BasicBehavior *move,BasicBehavior *rotate)
        :_model(model),_move(move),_rotate(rotate){}

    virtual void tick();
    virtual ~MonsterFleeMove(){}
private:
    MonsterModel* _model;
    BasicBehavior* _move;
    BasicBehavior* _rotate;

    BehaviorStatus _rotation_status = BehaviorStatus::fail;
};


}
#endif // MONSTERSM_H
