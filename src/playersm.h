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

namespace Monster {
class Monster;
}

class PlayerSm {
public:
    virtual void move() = 0;
    virtual void updateEnergy() = 0;
    virtual void toggleRage() = 0;
    virtual void collisionWithMonster(Monster::Monster *m) = 0;
    virtual void enter() {}
    virtual void exit() {}
    virtual ~PlayerSm();
protected:
    int _max_speed;
    double _max_speed_45;
    PlayerModel* _model = nullptr;
    Animation *_animation = nullptr;
public:
    void moveBy(double step_x, double step_y);
};

class PlayerNormal: public PlayerSm {
public:
    PlayerNormal(PlayerModel* model);

    virtual void updateEnergy() override;

    virtual void move() override ;

    virtual void collisionWithMonster(Monster::Monster *m) override ;

    virtual void toggleRage() override;
    virtual ~PlayerNormal() override;

};

class PlayerRageAvailable: public PlayerNormal {
public:
    PlayerRageAvailable(PlayerModel* model)
        :PlayerNormal(model){}
    virtual void updateEnergy() override {
        return;
    }
    virtual void toggleRage() override ;

};

class PlayerOnDamage: public PlayerNormal {
public:
    PlayerOnDamage(PlayerModel* model);

    virtual void enter() override final;
    virtual void exit() override final;

    virtual void updateEnergy() override ;

    virtual void collisionWithMonster(Monster::Monster *m) override {
    	Q_UNUSED(m)
        return;
    }
    virtual ~PlayerOnDamage();

private:
    int no_damage_counter = 100;
};

class PlayerOnRage: public PlayerSm {
public:
    PlayerOnRage(PlayerModel* model);

    virtual void updateEnergy() override;

    virtual void move() override;
    virtual void toggleRage() override ;
    virtual void collisionWithMonster(Monster::Monster *m) override;

    virtual ~PlayerOnRage() {};
private:

};

class PlayerDead: public PlayerSm {
public:
    PlayerDead(PlayerModel* model);

    virtual void enter() override final;

    virtual void move() override {}
    virtual void updateEnergy() override {}
    virtual void toggleRage() override {}
    virtual void collisionWithMonster(Monster::Monster *m) override {Q_UNUSED(m)}
    virtual ~PlayerDead();
private:
    Animation *death_animation;
};

#endif // PLAYERSM_H
