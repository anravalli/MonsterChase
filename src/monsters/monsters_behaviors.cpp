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

#include "monsters_behaviors.h"
#include <math.h>       /* cos */

#include "base_game/gameworld.h"
#include "base_game/arena.h"
#include "player/player.h"
#include "lib/algorithms.h"

#define PI 3.14159265

#define TORAD(x) x*PI/180
#define TODEG(x) x*180/PI


MonsterBasicBehavior::~MonsterBasicBehavior() {}

/*
 * Direction selection Behaviors
 */
RandomDirection::RandomDirection(Monster::MonsterModel *m):
    MonsterBasicBehavior(m)
{
    std::random_device r;
    std::default_random_engine engine(r());
    std::uniform_int_distribution<int> distribution(0,359);
    _direction = std::bind(distribution, engine);
}

BehaviorStatus RandomDirection::exec() {
    _model->target_direction = _direction();

    return success;
}

PerpendicularDirection::PerpendicularDirection(Monster::MonsterModel *m):
    MonsterBasicBehavior(m)
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
    double rem = std::fmod(_model->target_direction, 90.0);
    if ( std::round(rem) == 0 )
        _model->target_direction = static_cast<int>(_model->target_direction + sign*90);
    else if (rem > 45)
        _model->target_direction = (static_cast<int>(_model->target_direction / 90)+1)*90;
    else
        _model->target_direction -= rem;

    //TODO: negative values workaraound - to be reviewed
    if (_model->target_direction < 0)
        _model->target_direction += 360;

    if (_model->target_direction >= 360)
        _model->target_direction -= 360;

    return success;
}

/*
 * Move Behaviors
 */

MoveToTarget::MoveToTarget(Monster::MonsterModel *m, int speed):
    MonsterBasicBehavior(m), _speed(speed)
{
}

BehaviorStatus MoveToTarget::exec() {
    BehaviorStatus status = success;
    double actual_speed = _speed;

    int dist_x = (_model->target_x - _model->pos_x) ;
    int dist_y = (_model->target_y - _model->pos_y) ;

    double t_dist = sqrt((dist_x*dist_x)+(dist_y*dist_y));

    if (t_dist > 0){
        if (t_dist < _speed)
            actual_speed = t_dist;

        double dy = sin( TORAD(_model->direction) ) * actual_speed;
        double dx = cos ( TORAD(_model->direction) ) * actual_speed;
        //save previoius position
        _model->prev_pos_x = _model->pos_x;
        _model->prev_pos_y = _model->pos_y;
        //update the current position
        _model->pos_x += dx;
        _model->pos_y += dy;

        status = running;
    }

    return status;
}

BehaviorStatus MoveRandomSteps::exec() { abort(); }

BehaviorStatus MoveFixedSteps::exec() {
    BehaviorStatus status = success;
    if (_counter < _steps){
        double dx = cos ( TORAD(_model->direction) ) * _speed;
        double dy = sin( TORAD(_model->direction) ) * _speed;
        //save previoius position
        _model->prev_pos_x = _model->pos_x;
        _model->prev_pos_y = _model->pos_y;
        //update the current position
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
    double actual_speed = _speed;

    if (abs(_model->target_direction - _model->direction)<_speed)
        actual_speed = abs(_model->target_direction - _model->direction);

    if (_model->target_direction > _model->direction){
        if ( (_model->target_direction - _model->direction) > 180) {
            _model->direction -= actual_speed; // cw
        }
        else
            _model->direction += actual_speed; // ccw
        status = running;
    }
    else if (_model->target_direction < _model->direction){
        if ( (_model->direction - _model->target_direction) > 180) {
            _model->direction += actual_speed; // ccw
        }
        else
            _model->direction -= actual_speed; // cw
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


/*
 * Checking Behaviors
 */

#define speed_x(m) cos(TORAD(m->direction))*m->curent_speed
#define speed_y(m) sin(TORAD(m->direction))*m->curent_speed

BehaviorStatus WallsCollisionChecker::exec()
{
    //model.pos is the center of the collision box
    //getWallsAround needs the top-left and bottom-right corners
    std::vector<Brick*> walls = GameWorld::instance().getWallsAround(QPointF(_model->pos_x-(_entity_size/2),
                                                                                _model->pos_y-(_entity_size/2)),
                                                                        QPointF(_model->pos_x+(_entity_size/2),
                                                                                _model->pos_y+(_entity_size/2)));
    BehaviorStatus status = fail;

    QRectF collisionBox(_model->pos_x-_entity_size/2, _model->pos_y-_entity_size/2,
                          _entity_size, _entity_size);

    for (auto b: walls){
        //test: increase displacement due to collisions glitch
        QRectF i = collisionBox.intersected(b->boundingRect());

        if (not i.isEmpty()){
            //we have at least a collision so the behavior succeded
            status = success;
            QPointF new_pos = collisionPointFinder::find_substep3(
                        collisionBox,
                        b->boundingRect(),
                        QPointF(speed_x(_model),speed_y(_model)), 5);
            _model->pos_x = new_pos.x();
            _model->pos_y = new_pos.y();}
    }
    return status;
}

BehaviorStatus EntitiesCollisionChecker::exec()
{
    BehaviorStatus status = fail;
    QRectF pbox = GameWorld::instance().getPlayer()->collisionBox();
    QRectF collisionBox(_model->pos_x-_entity_size/2, _model->pos_y-_entity_size/2,
                          _entity_size, _entity_size);
    QPointF new_pos = QPointF(_model->pos_x, _model->pos_y);

    Monster::Monster* this_monster = nullptr;
    std::vector<Monster::Monster*> monsters = GameWorld::instance().getMonsters();
    for (auto m: monsters){
        if (m->id() == _model->id){
        	this_monster = m;
        	continue;
        }
        QRectF i = collisionBox.intersected(m->collisionBox());
        if (not i.isEmpty()){
            status = success;
            new_pos = collisionPointFinder::find_substep3(
                        collisionBox,
                        m->collisionBox(),
                        QPointF(speed_x(_model),speed_y(_model)),
                        5);
        }
    }

    QRectF i = collisionBox.intersected(pbox);
    if (not i.isEmpty()){
        GameWorld::instance().getPlayer()->collisionWithMonster(this_monster);
        status = success;
        new_pos = collisionPointFinder::find_substep3(
                    collisionBox,
                    pbox,
                    QPointF(speed_x(_model),speed_y(_model)),
                    5);
        collisionBox.moveCenter(new_pos);
    }

    _model->pos_x = new_pos.x();
    _model->pos_y = new_pos.y();

    return status;
}

PlayerAtSightChecker::PlayerAtSightChecker(Monster::MonsterModel *m, int size):
    MonsterBasicBehavior(m), _entity_size(size)
{
}

BehaviorStatus PlayerAtSightChecker::exec()
{
    BehaviorStatus status = fail;
    QRectF pbox = GameWorld::instance().getPlayer()->collisionBox();

    Monster::Monster* this_monster = nullptr;
    std::vector<Monster::Monster*> monsters = GameWorld::instance().getMonsters();
    for (auto m: monsters){
        if (m->id() == _model->id) this_monster = m;
    }

    QRectF i = this_monster->sightBox().intersected(pbox);
    if (not i.isEmpty()){
        status = inRange(pbox.center());
    }

    return status;
}

BehaviorStatus PlayerAtSightChecker::inRange(QPointF pc)
{
    BehaviorStatus ret = fail;

    //range checked starting from shapes center: sight range will result
    //a little bit wider than the drawn one
    double dx = pc.x() - _model->pos_x;
    double dy = pc.y() - _model->pos_y;

    double p_dist = sqrt(dx*dx + dy*dy);
    double p_dir = atan2(dy, dx);
    //qudrant adjutment
    if (p_dir<0)
        p_dir = 2*PI+p_dir;

#if DEBUG
    double p_dir_deg = TODEG(p_dir);
#endif

    double sight_up = TORAD((_model->direction+40));
    double sight_down = TORAD((_model->direction-40));

    if (p_dir < sight_up and p_dir > sight_down and p_dist <= 180){
        _model->target_direction = TODEG(p_dir);
        _model->target_x = pc.x();
        _model->target_y = pc.y();
        ret = success;
    }
    return ret;
}

PlayerProximityChecker::PlayerProximityChecker(Monster::MonsterModel *m, int size):
    MonsterBasicBehavior(m), _entity_size(size)
{
}

BehaviorStatus PlayerProximityChecker::exec()
{
    BehaviorStatus status = fail;
    Player* p = GameWorld::instance().getPlayer();
    QRectF pbox = p->collisionBox();

    Monster::Monster* this_monster = nullptr;
    std::vector<Monster::Monster*> monsters = GameWorld::instance().getMonsters();
    for (auto m: monsters){
        if (m->id() == _model->id) this_monster = m;
    }

    QRectF i = this_monster->warningBox().intersected(pbox);
    if (not i.isEmpty()){
        status = fineCheck(pbox.center());
    }

    return status;
}

BehaviorStatus PlayerProximityChecker::fineCheck(QPointF pc)
{
    BehaviorStatus ret = fail;

    //range checked starting from shapes center: sight range will result
    //a little bit wider than the drawn one
    double dx = pc.x() - _model->pos_x;
    double dy = pc.y() - _model->pos_y;

    double p_dist = sqrt(dx*dx + dy*dy);

#if DEBUG
    double p_dir = atan2(dy, dx);
    //qudrant adjutment
    if (p_dir<0)
        p_dir = 2*PI+p_dir;

    double p_dir_deg = TODEG(p_dir);

    double sight_up = TORAD((_model->direction+40));
    double sight_down = TORAD((_model->direction-40));

#endif

    if (p_dist <= 100){
		_model->target_x = -pc.x();
		_model->target_y = -pc.y();
		ret = success;
    }

    return ret;
}
