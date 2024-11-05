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


#include "gameworld.h"

#include "player/player.h"
#include "monsters/monster.h"
#include "arena.h"
#include "gameconfig.h"

GameWorld::GameWorld(){}

GameWorld::~GameWorld(){}

GameWorld& GameWorld::instance()
{
    static GameWorld instance;
    return instance;
}

void GameWorld::start()
{
    player->show();
    for (auto m: monsters)
        m->show();
}

void GameWorld::nextFrame()
{
    player->update();
    for(auto it = monsters.begin(); it != monsters.end();){
        auto m = *it;
        if(m->isAlive()){
            m->update();
            it++;
            continue;
        }
        delete m;
        it = monsters.erase(it);
    }
}

void GameWorld::initLevel(QString map)
{
    arena = new Arena(map, GameConfig::playground_width/MAP_WIDTH);
    addPlayer();
    addMonsters();
}

void GameWorld::deInitLevel()
{
	delete player;
	for (auto m: monsters)
		delete m;
	monsters.clear();

	delete arena;
}

void GameWorld::addPlayer()
{
    player = new Player();
    player->setEnergyGaugePos(
                GameConfig::playground_width/2,
                GameConfig::playground_height+GameConfig::playground_border_height*0.3);
    player->setScorePos(
                GameConfig::playground_width-35,
                -GameConfig::playground_border_height*0.6);
    player->hide();
}

void GameWorld::addMonsters()
{
    //Adding Blinky at x=200 y=200
    Monster::Monster* m = Monster::monsterFactory(
                Monster::MonsterType::Blinky,
                QPointF(200,200));
    m->hide();
    monsters.push_back(m);

    //Adding Pinky at x=600 y=200
    m = Monster::monsterFactory(
                Monster::MonsterType::Pinky,
                QPointF(600,200));
    m->hide();
    monsters.push_back(m);
}

std::vector<Monster::Monster*> GameWorld::getMonsters()
{
    return monsters;
}

std::vector<Brick*> GameWorld::getWallsAround(QPointF tl, QPointF br)
{
    std::pair<int,int> tl_idx = arena->posToIdx(tl);
    std::pair<int,int> br_idx = arena->posToIdx(br);
    std::pair<int,int> idx;
    std::vector<Brick*> wall;
    for(int x=tl_idx.first-1; x<br_idx.first+1; x++){
        for (int y=tl_idx.second-1; y<br_idx.second+1; y++){
            //TODO
            idx.first = y;
            idx.second = x;
            Brick* b = arena->getBrick(idx);
            if (!(b==nullptr))
                wall.push_back(b);
        }
    }
    return wall;
}

Player *GameWorld::getPlayer()
{
    return player;
}

Arena *GameWorld::getArena()
{
    return arena;
}



