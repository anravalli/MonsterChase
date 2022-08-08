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
 * matchmenu.h: created on: 25 lug 2022
 */

#ifndef SRC_MATCHMENU_H_
#define SRC_MATCHMENU_H_

#include <ui_framework/uipagemenu.h>
#include <ui_framework/uipagemenuwidgets_qt.h>

class SelectionMenuWidget_qt: public UiPageMenuWidget_qt
{
public:
	SelectionMenuWidget_qt(vector<QString> model);

	virtual QString get_item_label(int item_idx) override final;

	virtual double set_item_label(int item_idx, QString new_label)
			override final;

	void next_value_for(unsigned int idx);

	void previous_value_for(unsigned int idx);

	void update_and_realign(double item_width);

	int get_current_value_of(unsigned int idx);

	void change_current_value_of(unsigned int item_idx, unsigned int val_idx);
};


class PopupSelectionMenuWidget_qt: public UiPagePopupWidget_qt
{
public:
	PopupSelectionMenuWidget_qt(QString info, UiPageMenuWidget_qt *menu);

	void select_prev_for(int idx);

	void select_next_for(int idx);
};


class MatchPlayerSelectionMenu: public UiPageMenu
{
	Q_OBJECT
public:
	MatchPlayerSelectionMenu(vector<function<void()>> actions, UiPageAbstractMenuWidget *view, int start_index = 0):
		UiPageMenu(actions, view, start_index){};
public:
	void next_value_for(unsigned int idx);

	void previous_value_for(unsigned int idx);
signals:
	void name_changed(QString new_name);
	void match_changed(QString new_match);
};


class MatchMenu: public UiPageMenu
{
	Q_OBJECT
public:
	MatchMenu(vector<function<void()> > actions,
			UiPageAbstractMenuWidget *view);

	virtual ~MatchMenu(){};
public slots:
	void on_player_name_changed(QString new_name);
	void on_match_type_changed(QString new_match);
private:
};

class MatchMenuWidget_qt: public UiPageMenuWidget_qt
{
public:
	MatchMenuWidget_qt(vector<QString> *model): UiPageMenuWidget_qt(model){}
	virtual double set_item_label(int item_idx, QString new_label) override final;

};

#endif /* SRC_MATCHMENU_H_ */
