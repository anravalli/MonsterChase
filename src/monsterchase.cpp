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

#include "monsterchase.h"
#include "gamecontroller.h"

/*
 * Here we will build all the game objects responsible for the
 * game business logic, including the UI pages and game controllers.
 */

MonsterChase::MonsterChase()
{
    game_controller = new GameController(this);
}

MonsterChase::~MonsterChase()
{
    delete game_controller;
}

void MonsterChase::show()
{
    game_controller->show();
}


