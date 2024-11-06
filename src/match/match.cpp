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
 *  Created on: 26 ott 2022
 *      Author: Andrea Ravalli
 */

#include "match.h"
#include "base_game/gameworld.h"
#include "base_game/gameconfig.h"
#include "player/player.h"

Match *matchFactory(MatchType type, QString profile)
{
	qDebug("Creating \"%s\" match for %s",match_type_tostr(type), profile.toStdString().c_str());
	Match *match = nullptr;
	switch(type)
	{
	case mt_hunter:
	case mt_survivor:
	case mt_the_dark_hunt:
	case mt_alone_in_the_dark:
		match = new Match();
		match->match_type = type;
		break;
	default:
		break;
	}
	assert(match);

	match->player_profile = profile;

	return match;
}

Match::Match() {
	map_name = ":/resources/map.txt";

	frame_max = frame_counter = GameConfig::framerate;
}

Match::~Match() {
	// TODO Auto-generated destructor stub
}

MatchResult Match::check_rules() {

	if(GameWorld::instance().getPlayer()->isDead()){
		//you loose!
		match_result = mr_loose;
		player_score = GameWorld::instance().getPlayer()->getScore();
		player_energy = GameWorld::instance().getPlayer()->getEnergy();

	}
	if(GameWorld::instance().getMonsters().empty()){
		//you win!
		match_result = mr_win;
	}
	if(match_result == mr_continue)
		update_play_time(); //other match type may contemplate a decreasing play time

	return match_result;
}

int Match::compute_match_score()
{
	int final_score = player_score;
	if (match_result == mr_win)
		final_score =+ player_energy*10 - play_time;

	if (final_score<0)
		final_score = 0;

	return final_score;
}

QString Match::get_match_completion_prompt()
{
	QString prompt = "Keep Going!";
	switch(match_result){
	case mr_loose:
		prompt = "GAME OVER: You Loose!";
		break;
	case mr_win:
		prompt = "The hunt is over: You Win!";
		break;
	default:
		break;
	}
	return prompt;
}

void Match::update_play_time(){
    if(!frame_counter){
        frame_counter=frame_max;
        play_time++;
    }
    else
        frame_counter--;
    return;
}

const char *match_type_tostr(MatchType mt)
{
	static const char *mt_strings[] = {"no match", "hunter", "survivor", "the dark hunt", "alone in the dark"};
	return mt_strings[mt];
}

