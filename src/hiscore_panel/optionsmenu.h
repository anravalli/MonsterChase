/*
 * OptionsMenu.h
 *
 *  Created on: 12 giu 2022
 *      Author: andrea
 */

#ifndef SRC_OPTIONS_PANEL_OPTIONSMENU_H_
#define SRC_OPTIONS_PANEL_OPTIONSMENU_H_

#include "ui_framework/uipagemenu.h"
#include <vector>
#include <functional>

//widget object for name and values items
class OptionItem
{
public:
	OptionItem(QString _name, vector<QString> _values,
			int _default_idx, int _current_idx,
			function<void()> _action)
	: name(_name), values(_values),
	  default_idx(_default_idx), current_idx(_current_idx),
	  action(_action)
	{}

//private:
	QString name;
	vector<QString> values ;
	int default_idx;
	int current_idx;
	function<void()> action;
};

//controller part for the menu
class OptionsMenu: public UiPageMenu
{
public:
	OptionsMenu(vector<OptionItem> *model);
	virtual ~OptionsMenu();
	virtual bool handleKey(int key, bool released) override final;
	virtual void run_item_action(bool released) override final;
	int get_current_value_of(int idx);
	void change_current_value_of(int item_idx, int val_idx);
private:
	void select_next_value(bool released);
	void select_previous_value(bool released);

	vector<OptionItem> *model;
};

#endif /* SRC_OPTIONS_PANEL_OPTIONSMENU_H_ */
