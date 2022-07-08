/*
 * OptionsMenu.cpp
 *
 *  Created on: 12 giu 2022
 *      Author: andrea
 */

#include "optionsmenu.h"
#include <ui_framework/uipagemenuwidgets_qt.h>

OptionsMenu::OptionsMenu(vector<OptionItem> *model)
: model(model)
{
	vector<QString> names;
	for (auto item: *model)
	{
		names.push_back(item.name);
		actions.push_back(item.action);
	}
	last_item_index = this->actions.size()-1;
	//current_item_idx = start_index;

	view = new UiPageMenuWidget_qt(&names);

}

OptionsMenu::~OptionsMenu() {
	// TODO Auto-generated destructor stub
}

//void OptionsMenu::show()
//{
//}
//
//void OptionsMenu::hide()
//{
//}
//
//void OptionsMenu::activate()
//{
//}
//
//void OptionsMenu::deactivate()
//{
//}
//
//void OptionsMenu::addToPage(UiPageViewQt* page)
//{
//}
//
//void OptionsMenu::selectionChanged(int index)
//{
//}
//
//void OptionsMenu::setPos(double x, double y)
//{
//}
//
//void OptionsMenu::setAlignement(MenuAlignement a)
//{
//}
