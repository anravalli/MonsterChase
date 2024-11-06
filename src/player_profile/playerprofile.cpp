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

#include "playerprofile.h"
#include <QJsonArray>

PlayerProfile::PlayerProfile ()
{
	name = "noname";
	last_match = MatchType::mt_hunter;
	for(int i=0; i<4; i++){
		best_scores[i] = 0;
	}
}

PlayerProfile::PlayerProfile (QJsonObject po)
{
	name = po.value("name").toString("noname");
	//match type extraction should be checked for consistency
	last_match = (MatchType) po.value("last_match").toInt(1);
	auto scores = po.value("best_scores").toArray();
	for(int i=0; i<scores.size(); i++) {
		best_scores[i] = scores.at(i).toInt(0);
	};
}

PlayerProfile::~PlayerProfile ()
{
	// TODO Auto-generated destructor stub
}

PlayerProfile::PlayerProfile (const PlayerProfile &other)
{
	name = other.name;
	last_match = other.last_match;
	for(int i=0; i<4; i++){
		best_scores[i] = other.best_scores[i];
	}
}

PlayerProfile& PlayerProfile::operator= (const PlayerProfile &other)
{
	if (this == &other) {
		return *this;
	}
	name = other.name;
	last_match = other.last_match;
	for(int i=0; i<4; i++){
		best_scores[i] = other.best_scores[i];
	}
	return *this;
}

const int* PlayerProfile::getBestScores () const
{
	return best_scores;
}

void PlayerProfile::setBestScore (MatchType mt, int score)
{
	if(best_scores[mt] < score)
		best_scores[mt] = score;
	return;
}

MatchType PlayerProfile::getLastMatch () const
{
	return last_match;
}

void PlayerProfile::setLastMatch (MatchType lastMatch)
{
	last_match = lastMatch;
}

const QString& PlayerProfile::getName () const
{
	return name;
}

void PlayerProfile::setName (const QString &name)
{
	this->name = name;
}
