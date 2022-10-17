#ifndef GAMEWORLD_H
#define GAMEWORLD_H

/*
 *	Monster Chase: a testing playground for behaviors trees
 *
 *	Copyright 2021 Andrea Ravalli <anravalli @ gmail.com>
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


#include "QGraphicsScene"

class Arena;
class Brick;
class Player;
namespace Monster {
class Monster;
}

/*
 * This should be the system part of an ENTITY-SYSTEM structure,
 * acting then as collection/facade for the entities part of the system
 */

class GameWorld: public QObject
{
    Q_OBJECT

public:
    static GameWorld& instance();

    void initLevel(QString map);
    void deInitLevel();
    void nextFrame();

    std::vector<Monster::Monster*> getMonsters();
    std::vector<Brick*> getWallsAround(QPointF tl, QPointF br);
    Player *getPlayer();
    Arena *getArena();

    //avoid copy
    GameWorld(GameWorld const&) = delete;
    void operator=(GameWorld const&)  = delete;

    virtual ~GameWorld();

public slots:
    void start();

private:
    GameWorld();

    void addPlayer();
    void addMonsters();

protected:
    Arena* arena;
    Player* player;
    std::vector<Monster::Monster*> monsters;

};


#endif // GAMEWORLD_H
