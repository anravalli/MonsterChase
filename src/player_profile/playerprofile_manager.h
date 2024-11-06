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

#ifndef SRC_PLAYER_PROFILE_PLAYERPROFILE_MANAGER_H_
#define SRC_PLAYER_PROFILE_PLAYERPROFILE_MANAGER_H_

#include "playerprofile.h"
#include <vector>

class PlayerProfileManager
{
public:
	virtual ~PlayerProfileManager ();

	static PlayerProfileManager& instance()
	{
		static PlayerProfileManager me;
		return me;
	}

	std::vector<PlayerProfile> getPlayerProfiles()
	{
		return playerProfiles;
	}

	PlayerProfile& getPlayerProfile(QString name);

	void insertPlayerProfile(PlayerProfile p);

	//void updatePlayerProfile(QString name, PlayerProfile p);

private:
	PlayerProfileManager ();

	//std::map<QString, PlayerProfile> playerProfiles;
	std::vector<PlayerProfile> playerProfiles;
};

#endif /* SRC_PLAYER_PROFILE_PLAYERPROFILE_MANAGER_H_ */
