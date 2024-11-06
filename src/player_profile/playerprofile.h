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

#include <QJsonObject>
#include <vector>
#include "match/match.h"

#ifndef SRC_PLAYER_PROFILE_PLAYERPROFILE_H_
#define SRC_PLAYER_PROFILE_PLAYERPROFILE_H_

class PlayerProfile
{
public:
	PlayerProfile ();
	PlayerProfile (QJsonObject po);
	virtual ~PlayerProfile ();
	PlayerProfile (const PlayerProfile &other);
	PlayerProfile&
	operator= (const PlayerProfile &other);


	const int* getBestScores () const;
	void setBestScore (MatchType mt, int score);
	MatchType getLastMatch () const;
	void setLastMatch (MatchType lastMatch);
	const QString& getName () const;
	void setName (const QString &name);

private:
	QString name;
	MatchType last_match;
	int best_scores[4];
};


#endif /* SRC_PLAYER_PROFILE_PLAYERPROFILE_H_ */
