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

namespace Monster{

class MonsterSm {
public:
    virtual void tick() = 0;
    //virtual void toggleRage() = 0;
    //virtual void enter() = 0;
    //virtual void exit() = 0;
    virtual ~MonsterSm(){}
};

class MonsterPatrol: public MonsterSm {
public:
    MonsterPatrol(MonsterModel* model)
        :_model(model){}

    virtual void tick();
    virtual ~MonsterPatrol(){}

private:
    int _speed=2;
    int xsteps = 0;
    int ysteps = 0;
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
    int _speed=10;

    void move();
};

class MonsterFreeze: public MonsterSm {
public:
    MonsterFreeze(MonsterModel* model)
        :_model(model){}

    virtual void tick();
    virtual ~MonsterFreeze(){}
private:
    MonsterModel* _model;
    int _freeze_time=10;
};

}
#endif // MONSTERSM_H
