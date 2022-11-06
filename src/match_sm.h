/*
 *	Monster Chase: a testing playground for behaviors trees
 *
 *	Copyright 2022 Andrea Ravalli <anravalli @ gmail.com>
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
 *  Created on: 25 ott 2022
 */

#ifndef SRC_MATCH_SM_H_
#define SRC_MATCH_SM_H_

enum MatchStateE
{
//	ms_dummy,
	ms_running,
	ms_pused,
	ms_ended,
	ms_aborted
};

class GameController;

class MatchState {
public:
	virtual ~MatchState();
	virtual void enter() = 0;
	virtual void exit() {};
	virtual void next() = 0;
	virtual bool handleKey(int key, bool released) = 0;

protected:
	GameController *m_controller = nullptr;
};

MatchState *MatchStateFactory(MatchStateE state, GameController *controller);


#endif /* SRC_MATCH_SM_H_ */
