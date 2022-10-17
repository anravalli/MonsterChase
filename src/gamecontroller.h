#ifndef GAME_H
#define GAME_H

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


#include <ui_framework/uipagecontroller.h>

class UiPageViewQt;
class QTimer;
class PlayTime;
class UiPageMenu;

enum MatchType
{
	mt_no_match,
	mt_hunter,
	mt_survivor,
	mt_the_dark_hunt,
	mt_alone_in_the_dark
};

enum MatchState
{
	ms_running,
	ms_pused,
	ms_ended,
	ms_aborted
};

struct MatchData
{
	int play_time;
	QString player_profile;

};

//we need a Match object encapsulating all the match characteristics like match score, play time, player profile, match type and map
//the Match object could be in three different state: running, paused, terminated

class GameController : public UiPageController
{
    Q_OBJECT
public:
    explicit GameController(UiPageController *parent = nullptr);
    ~GameController() override;
    void show() override;
    void exit() override;


public slots:
    void gameStep() ;
    void start();

	MatchType get_match_type() const
	{
		return match_type;
	}

	void set_match_type(MatchType matchType)
	{
		match_type = matchType;
	}

protected:
    bool handleKey(int key, bool released) override;

private:
    QTimer* timer = nullptr;
    PlayTime* ptime = nullptr;
    UiPageMenu *current_menu = nullptr;
    UiPageMenu *pause_menu = nullptr;
    UiPageMenu *match_end_menu = nullptr;
    MatchType match_type = mt_hunter;

    bool is_paused; //temporary: this "state variable" has to be changed to a "real" state

    void initMatch();
    void addPlayTime();
    void checkMatchRules();
    void macthEnded(bool gameover);
    UiPageMenu *create_match_ended_popup(int score, int energy, int play_time,
    		int final_score, QString message);
    UiPageMenu *create_pause_menu();
    void togglePause();

signals:

};

#endif // GAME_H
