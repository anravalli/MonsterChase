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

//	virtual void show() override final;
//	virtual void hide() override final;
//	virtual void activate() override final;
//	virtual void deactivate() override final;
//
//	virtual void addToPage(UiPageViewQt* page) override final;
//	virtual void selectionChanged(int index) override final;
//	virtual void setPos(double x, double y) override final;
//	virtual void setAlignement(MenuAlignement a) override final;

private:
	vector<OptionItem> *model;
};

#endif /* SRC_OPTIONS_PANEL_OPTIONSMENU_H_ */
