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

#include "behaviors.h"
#include <math.h>       /* cos */

#define PI 3.14159265

/*
 * Direction selection Behaviors
 */
RandomDirection::RandomDirection(Monster::MonsterModel *m):
    BasicBehavior(m)
{
    std::random_device r;
    std::default_random_engine engine(r());
    std::uniform_int_distribution<int> distribution(0,359);
    _direction = std::bind(distribution, engine);
}

BehaviorStatus RandomDirection::exec() {
    _model->target_direction = _direction();
    //test
    _model->direction = _model->target_direction;
    return success;
}

PerpendicularDirection::PerpendicularDirection(Monster::MonsterModel *m):
    BasicBehavior(m)
{
    std::random_device r;
    std::default_random_engine engine(r());
    std::uniform_int_distribution<int> distribution(0,1);
    _clockwise = std::bind(distribution, engine);
}

BehaviorStatus PerpendicularDirection::exec() {
    int sign = 1;
    if (_clockwise())
        sign = -1;
    _model->target_direction += sign*90;

    //TODO: negative values workaraound - to be reviewed
    if (_model->target_direction < 0)
        _model->target_direction += 360;

    if (_model->target_direction >= 360)
        _model->target_direction -= 360;

    //test
    _model->direction = _model->target_direction;
    return success;
}

/*
 * Move Behaviors
 */
BehaviorStatus MoveFixedSteps::exec() {
    BehaviorStatus status = success;
    if (_counter < _steps){
        double dx = cos ( _model->direction * PI / 180.0 ) * _speed;
        double dy = sin( _model->direction * PI / 180.0 ) * _speed;
        _model->pos_x += dx;
        _model->pos_y += dy;
        _counter++;
        status = running;
    }
    else
        _counter = 0;

    return status;
}

/*
 * Rotation Behaviors
 */
BehaviorStatus LinearRotation::exec() {
    BehaviorStatus status = success;

    if (_model->target_direction > _model->direction){
        if ( (_model->target_direction - _model->direction) > 180) {
            _model->direction -= _speed; // cw
        }
        else
            _model->direction += _speed; // ccw
        status = running;
    }
    else if (_model->target_direction < _model->direction){
        if ( (_model->direction - _model->target_direction) > 180) {
            _model->direction += _speed; // ccw
        }
        else
            _model->direction -= _speed; // cw
        status = running;
    }

    if (_model->direction < 0)
        _model->direction += 360;

    if (_model->direction > 360)
        _model->direction -= 360;

    return status;
}

BehaviorStatus TronRotation::exec() {
    _model->direction = _model->target_direction;
    return success;
}
