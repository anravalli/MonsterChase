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

#include "match.h"
#include "match_sm.h"
#include <ui_framework/uipagecontroller.h>

class UiPageViewQt;
class QTimer;
class PlayTime;
class UiPageMenu;

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
    UiPageMenu * pause_menu();
    UiPageMenu * end_menu();
    Match *match();
    void set_match(Match *match);
    void change_match_state(MatchStateE next_state);

public slots:
    void gameStep();
    void start();

protected:
    bool handleKey(int key, bool released) override;

private:
    QTimer* timer = nullptr;
    PlayTime* ptime = nullptr;

    UiPageMenu *m_pause_menu = nullptr;
    UiPageMenu *m_end_menu = nullptr;
    Match *m_match;
    MatchState *match_states[4] = {0};
    MatchStateE current_state = ms_running;
    MatchType match_type = mt_hunter; //TO BE REVIEWED

    void initMatch();
    void addPlayTime();

    UiPageMenu *create_match_ended_popup();
    UiPageMenu *create_pause_menu();

signals:

};

inline UiPageMenu *GameController::pause_menu(){
	return m_pause_menu;
};

inline Match *GameController::match(){
	return m_match;
}

inline void GameController::set_match(Match *match)
{
	m_match = match;
}

#endif // GAME_H
