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

#include "player.h"

#ifndef PLAYERSM_H
#define PLAYERSM_H

//struct PlayerModel;

class PlayerSm {
public:
    virtual void move() = 0;
    virtual void updateEnergy() = 0;
    virtual void toggleRage() = 0;
    virtual void collisionWithMonster() = 0;
    //virtual void enter() = 0;
    //virtual void exit() = 0;
    virtual ~PlayerSm(){}
protected:
    int _max_speed;
    double _max_speed_45;
    PlayerModel* _model;
public:
    void moveBy(double step_x, double step_y);
};

class PlayerNormal: public PlayerSm {
public:
    PlayerNormal(PlayerModel* model);

    virtual void updateEnergy() override;

    virtual void move() override ;

    virtual void collisionWithMonster() override ;

    virtual void toggleRage() override;
    virtual ~PlayerNormal();

};

class PlayerRageAvailable: public PlayerNormal {
public:
    PlayerRageAvailable(PlayerModel* model)
        :PlayerNormal(model){}
    virtual void updateEnergy() override {
        //move();
        return;
    }
    virtual void toggleRage() override ;

//    virtual void collisionWithMonster() override ;

};

class PlayerOnDamage: public PlayerNormal {
public:
    PlayerOnDamage(PlayerModel* model)
        :PlayerNormal(model){}

    virtual void updateEnergy() override ;
    //virtual void toggleRage() override {    }

    virtual void collisionWithMonster() override {
        return;
    }
private:
    int no_damage_counter = 100;
};

class PlayerOnRage: public PlayerSm {
public:
    PlayerOnRage(PlayerModel* model);

    virtual void updateEnergy() override;

    virtual void move() override;
    virtual void toggleRage() override ;
    virtual void collisionWithMonster() override;

    virtual ~PlayerOnRage(){}
private:
    //PlayerModel* _model;

};

class PlayerDead: public PlayerSm {
public:
    PlayerDead(PlayerModel* model);

    virtual void move(){}
    virtual void updateEnergy(){}
    virtual void toggleRage(){}
    virtual void collisionWithMonster() override { }
    virtual ~PlayerDead(){}
private:
    //PlayerModel* _model;
};

#endif // PLAYERSM_H
