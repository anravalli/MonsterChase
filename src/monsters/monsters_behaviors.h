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


#ifndef MONSTERS_BEHAVIORS_H
#define MONSTERS_BEHAVIORS_H

#include "monsters/monster.h"
#include <lib/behaviors.h>

#include <random>
#include <functional>

class MonsterBasicBehavior: public Behavior
{
public:
    MonsterBasicBehavior(Monster::MonsterModel* m): _model(m) {}
//    virtual BehaviorStatus exec() = 0;
    virtual ~MonsterBasicBehavior();

protected:
    Monster::MonsterModel* _model;
};

/*
 * Direction selection Behaviors
 */
class RandomDirection: public MonsterBasicBehavior
{
public:
    RandomDirection(Monster::MonsterModel* m);
    BehaviorStatus exec() override;

private:
    std::function<int ()> _direction;
};

class PerpendicularDirection: public  MonsterBasicBehavior
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
class MoveToTarget: public  MonsterBasicBehavior
{
public:
    MoveToTarget(Monster::MonsterModel* m, int speed);
    BehaviorStatus exec() override;

private:
    int _speed;
};

class MoveFixedSteps: public  MonsterBasicBehavior
{
public:
    MoveFixedSteps(Monster::MonsterModel* m, int speed, int steps):
        MonsterBasicBehavior(m), _steps(steps), _speed(speed){}
    BehaviorStatus exec() override;

private:
    int _steps;
    int _speed;
    int _counter = 0;
};

class MoveRandomSteps: public  MonsterBasicBehavior
{
public:
    MoveRandomSteps(Monster::MonsterModel* m):
        MonsterBasicBehavior(m){}
    BehaviorStatus exec() override;

private:
    std::function<int ()> _steps_gen;
    int _steps;
    int _counter = 0;
};

/*
 * Rotation Behaviors
 */
class LinearRotation: public  MonsterBasicBehavior
{
public:
    LinearRotation(Monster::MonsterModel* m, int speed):
        MonsterBasicBehavior(m), _speed(speed){}
    BehaviorStatus exec() override;

private:
    int _speed;
    int _counter = 0;
};

class TronRotation: public  MonsterBasicBehavior
{
public:
    TronRotation(Monster::MonsterModel* m):
        MonsterBasicBehavior(m){}
    BehaviorStatus exec() override;
};

/*
 * Checking Behaviors
 */
class WallsCollisionChecker: public  MonsterBasicBehavior
{
public:
    WallsCollisionChecker(Monster::MonsterModel* m, int size):
        MonsterBasicBehavior(m), _entity_size(size){}
    BehaviorStatus exec() override;
private:
    int _entity_size;
};

class EntitiesCollisionChecker: public  MonsterBasicBehavior
{
public:
    EntitiesCollisionChecker(Monster::MonsterModel* m, int size):
        MonsterBasicBehavior(m), _entity_size(size){}
    BehaviorStatus exec() override;
private:
    int _entity_size;
};

class PlayerAtSightChecker: public  MonsterBasicBehavior
{
public:
    PlayerAtSightChecker(Monster::MonsterModel* m, int size);
    BehaviorStatus exec() override;
private:
    int _entity_size;
    BehaviorStatus inRange(QPointF pc);
};

class PlayerProximityChecker: public  MonsterBasicBehavior
{
public:
    PlayerProximityChecker(Monster::MonsterModel* m, int size);
    BehaviorStatus exec() override;
private:
    int _entity_size;
    BehaviorStatus fineCheck(QPointF pc);
};

#endif // MONSTERS_BEHAVIORS_H
