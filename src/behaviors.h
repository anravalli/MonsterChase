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


#ifndef BEHAVIORS_H
#define BEHAVIORS_H

#include "monster.h"

#include <random>
#include <functional>

enum BehaviorStatus {
    fail,
    success,
    running
};

class BasicBehavior
{
public:
    BasicBehavior(Monster::MonsterModel* m): _model(m) {}
    virtual BehaviorStatus exec() = 0;
    virtual ~BasicBehavior();

protected:
    Monster::MonsterModel* _model;
};

class Sequence: BasicBehavior{
public:
    Sequence(Monster::MonsterModel* m);
    BehaviorStatus exec() override{
        BehaviorStatus status = success;
        for (auto c: childs){
            status = c->exec();
            if (fail == status)
                break;
        };
        return status;
    }
protected:
    void addChild(BasicBehavior*);
private:
    std::vector<BasicBehavior*> childs;
};

/*
 * Direction selection Behaviors
 */
class RandomDirection: public BasicBehavior
{
public:
    RandomDirection(Monster::MonsterModel* m);
    BehaviorStatus exec() override;

private:
    std::function<int ()> _direction;
};

class PerpendicularDirection: public  BasicBehavior
{
public:
    PerpendicularDirection(Monster::MonsterModel* m);
    BehaviorStatus exec() override;

private:
    std::function<int ()> _clockwise;
};


/*
 * Move Behaviors
 */
class MoveToTarget: public  BasicBehavior
{
public:
    MoveToTarget(Monster::MonsterModel* m, int speed);
    BehaviorStatus exec() override;

private:
    int _speed;
};

class MoveFixedSteps: public  BasicBehavior
{
public:
    MoveFixedSteps(Monster::MonsterModel* m, int speed, int steps):
        BasicBehavior(m), _steps(steps), _speed(speed){}
    BehaviorStatus exec() override;

private:
    int _steps;
    int _speed;
    int _counter = 0;
};

class MoveRandomSteps: public  BasicBehavior
{
public:
    MoveRandomSteps(Monster::MonsterModel* m):
        BasicBehavior(m){}
    BehaviorStatus exec() override;

private:
    std::function<int ()> _steps_gen;
    int _steps;
    int _counter = 0;
};

/*
 * Rotation Behaviors
 */
class LinearRotation: public  BasicBehavior
{
public:
    LinearRotation(Monster::MonsterModel* m, int speed):
        BasicBehavior(m), _speed(speed){}
    BehaviorStatus exec() override;

private:
    int _speed;
    int _counter = 0;
};

class TronRotation: public  BasicBehavior
{
public:
    TronRotation(Monster::MonsterModel* m):
        BasicBehavior(m){}
    BehaviorStatus exec() override;
};

/*
 * Checking Behaviors
 */
class WallsCollisionChecker: public  BasicBehavior
{
public:
    WallsCollisionChecker(Monster::MonsterModel* m, int size):
        BasicBehavior(m), _entity_size(size){}
    BehaviorStatus exec() override;
private:
    int _entity_size;
};

class EntitiesCollisionChecker: public  BasicBehavior
{
public:
    EntitiesCollisionChecker(Monster::MonsterModel* m, int size):
        BasicBehavior(m), _entity_size(size){}
    BehaviorStatus exec() override;
private:
    int _entity_size;
};

class PlayerAtSightChecker: public  BasicBehavior
{
public:
    PlayerAtSightChecker(Monster::MonsterModel* m, int size);
    BehaviorStatus exec() override;
private:
    int _entity_size;
    BehaviorStatus inRange(QPointF pc);
};


#endif // BEHAVIORS_H
