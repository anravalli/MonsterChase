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

enum MatchType
{
	mt_no_match,
	mt_hunter,
	mt_survivor,
	mt_the_dark_hunt,
	mt_alone_in_the_dark
};

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

    MatchType match_type = mt_hunter;

    bool is_paused; //temporary: this "state variable" has to be changed to a "real" state

    void addPlayTime();

signals:

};

#endif // GAME_H
