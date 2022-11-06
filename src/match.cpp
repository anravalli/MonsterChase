/*
 * match.cpp
 *
 *  Created on: 26 ott 2022
 *      Author: andrea
 */

#include "match.h"
#include "gameworld.h"
#include "player.h"
#include "gameconfig.h"

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

