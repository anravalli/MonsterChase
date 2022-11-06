/*
 * match.h
 *
 *  Created on: 26 ott 2022
 *      Author: andrea
 */

#ifndef SRC_MATCH_H_
#define SRC_MATCH_H_

#include <QString>

enum MatchType
{
	mt_no_match,
	mt_hunter,
	mt_survivor,
	mt_the_dark_hunt,
	mt_alone_in_the_dark
};

enum MatchResult
{
	mr_continue,
	mr_win,
	mr_loose
};

class Match;
Match *matchFactory(MatchType type, QString profile);

const char *match_type_tostr(MatchType mt);

class Match {
public:
	friend Match *matchFactory(MatchType type, QString profile);

	virtual ~Match();

	//strategies
	virtual MatchResult check_rules();
	virtual int compute_match_score();
	virtual QString get_match_completion_prompt();
	void update_play_time();

	QString getMapName() const {
		return map_name;
	}

	MatchType getMatchType() const {
		return match_type;
	}

	int getPlayTime() const {
		return play_time;
	}

	QString getPlayerProfile() const {
		return player_profile;
	}

	int getPlayerEnergy() const {
		return player_energy;
	}

	int getPlayerScore() const {
		return player_score;
	}

protected:
	Match();

	QString player_profile = "no name";
	QString map_name = "";
	MatchType match_type = mt_hunter;

private:
	int play_time = 0;
	MatchResult match_result = mr_continue;

	int player_score = 0;
	int player_energy = 0;

    unsigned short frame_max;
    int frame_counter;
};




#endif /* SRC_MATCH_H_ */
;
