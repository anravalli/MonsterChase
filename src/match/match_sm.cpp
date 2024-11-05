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

#include "match_sm.h"
#include <base_game/gameworld.h>
#include <base_game/gameconfig.h>
#include <base_game/gamecontroller.h>
#include <lib/ui_framework/uipagecontroller.h>
#include <lib/ui_framework/uipagemenu.h>
#include <player/player.h>

MatchState::~MatchState() {
	// TODO Auto-generated destructor stub
}

class MatchRunning: public MatchState
{
public:
	MatchRunning(GameController *controller){
		m_controller = controller;
	}

	virtual ~MatchRunning(){};

	virtual void enter() override final {

	}

	virtual void exit() override final {

	}

	virtual void next() override final {
		MatchResult res = m_controller->match()->check_rules();
		if(res == mr_continue)
			GameWorld::instance().nextFrame();
		else
			m_controller->change_match_state(ms_ended);
	}

	virtual bool handleKey(int key, bool released) override final{
		bool ret = false;

		switch(key){
		case Qt::Key_Space:
		case Qt::Key_D:
		case Qt::Key_Right:
		case Qt::Key_A:
		case Qt::Key_Left:
		case Qt::Key_Up:
		case Qt::Key_W:
		case Qt::Key_S:
		case Qt::Key_Down:
		case Qt::Key_Enter:
		case Qt::Key_Return:
			ret = GameWorld::instance().getPlayer()->handleKey(key, released);
			break;
		case Qt::Key_Exit:
		case Qt::Key_Escape:
			if (released) m_controller->change_match_state(ms_pused);
			ret = true;
			break;
		default:
			break;
		}
		return ret;
	}
};

class MatchPaused: public MatchState
{
public:
	MatchPaused(GameController *controller){
		m_controller = controller;
	}

	virtual ~MatchPaused(){};

	virtual void enter() override final {
		m_controller->pause_menu()->show();
	}

	virtual void exit() override final {
		m_controller->pause_menu()->hide();
	}

	virtual void next() override final {
		//game paused: nothing to do
		return;
	}

	virtual bool handleKey(int key, bool released) override final{

		bool ret = false;

		switch(key){
		case Qt::Key_Space:
		case Qt::Key_D:
		case Qt::Key_Right:
		case Qt::Key_A:
		case Qt::Key_Left:
		case Qt::Key_Up:
		case Qt::Key_W:
		case Qt::Key_S:
		case Qt::Key_Down:
		case Qt::Key_Enter:
		case Qt::Key_Return:
			ret = m_controller->pause_menu()->handleKey(key, released);
			break;
		case Qt::Key_Exit:
		case Qt::Key_Escape:
			if (released) m_controller->change_match_state(ms_running);
			ret = true;
			break;
		default:
			break;
		}
		return ret;

	}
};

class MatchEnded: public MatchState
{
public:
	MatchEnded(GameController *controller){
		m_controller = controller;
	}

	virtual ~MatchEnded(){};

	virtual void enter() override final {
		GameWorld::instance().getPlayer()->hide();
		m_controller->end_menu()->show();
	}

	virtual void exit() override final {
		//collect all game statistics & exit
	}

	virtual void next() override final {
		GameWorld::instance().nextFrame();
	}

	virtual bool handleKey(int key, bool released) override final{

		bool ret = false;

		switch(key){
		case Qt::Key_Space:
		case Qt::Key_D:
		case Qt::Key_Right:
		case Qt::Key_A:
		case Qt::Key_Left:
		case Qt::Key_Up:
		case Qt::Key_W:
		case Qt::Key_S:
		case Qt::Key_Down:
		case Qt::Key_Enter:
		case Qt::Key_Return:
		case Qt::Key_Exit:
		case Qt::Key_Escape:
			ret = m_controller->end_menu()->handleKey(key, released);
			break;
		default:
			break;
		}
		return ret;

	}
};

class MatchAborted: public MatchState
{
public:
	MatchAborted(GameController *controller){
		m_controller = controller;
	}

	virtual ~MatchAborted(){};

	virtual void enter() override final {

	}

	virtual void exit() override final {

	}

	virtual void next() override final {
		;
	}

	virtual bool handleKey(int key, bool released) override final{
		Q_UNUSED(key)
		Q_UNUSED(released)
		return true;
	}
};

MatchState *MatchStateFactory(MatchStateE state, GameController *controller)
{
	MatchState *new_state = nullptr;
	switch(state)
	{
	case ms_running:
		new_state = new MatchRunning(controller);
		break;
	case ms_pused:
		new_state = new MatchPaused(controller);
		break;
	case ms_ended:
		new_state = new MatchEnded(controller);
		break;
	case ms_aborted:
		new_state = new MatchAborted(controller);
		break;
	default:
		break;
	}
	return new_state;
}
