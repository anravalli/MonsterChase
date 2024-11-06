/*
 *	Monster Chase: a testing playground for behaviors trees
 *
 *	Copyright 2024 Andrea Ravalli <anravalli @ gmail.com>
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
 *
 *  Created on: 5 nov 2024
 *      Author: Andrea Ravalli
 */

#include "playerprofile_manager.h"
#include "lib/persistence.h"

PlayerProfileManager::~PlayerProfileManager ()
{
	// TODO Auto-generated destructor stub
}

PlayerProfileManager::PlayerProfileManager ()
{
	auto players = Persistence::instance().getPlayers();
	qDebug("number of player: %d", players.size());
	for(auto o: players){
		PlayerProfile player(o.toObject());
		playerProfiles.push_back(player);
	}
}

PlayerProfile& PlayerProfileManager::getPlayerProfile(QString name)
{

	auto name_is = [name](const PlayerProfile& p) {
        return p.getName() == name;
    };
	auto profile = std::find_if(playerProfiles.begin(), playerProfiles.end(), name_is);

	return *profile;
}

void PlayerProfileManager::insertPlayerProfile(PlayerProfile p)
{
	//checking the existence of a duplicate is overkilling
	//let's proceed with the insertion right away
	playerProfiles.push_back(p);
}

/*
void PlayerProfileManager::updatePlayerProfile(QString name, PlayerProfile p)
{
	for (unsigned int i=0; i<playerProfiles.size(); i++){
		if(playerProfiles[i].getName() == p.getName()){
			playerProfiles[i] = p;
			break;
		}
	}
}
*/


