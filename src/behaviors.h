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

class BasicBehavior
{
public:
    BasicBehavior(Monster::MonsterModel* m): _model(m) {}
    virtual void exec() = 0;

protected:
    Monster::MonsterModel* _model;
};

class RandomDirection: public BasicBehavior
{
public:
    RandomDirection(Monster::MonsterModel* m);
    void exec() override;

private:
    std::function<int ()> _direction;
};

class PerpendicularDirection: public  BasicBehavior
{
public:
    PerpendicularDirection(Monster::MonsterModel* m);
    void exec() override;

private:
    std::function<int ()> _clockwise;
};


#endif // BEHAVIORS_H
