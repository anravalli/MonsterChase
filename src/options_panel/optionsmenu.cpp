/*
 * OptionsMenu.cpp
 *
 *  Created on: 12 giu 2022
 *      Author: andrea
 */

#include "optionsmenu.h"
#include <ui_framework/uipagemenuwidgets_qt.h>

class OptionMenuItemWidget_qt: public UiAbstractMenuItemWidget
{
public:
	OptionMenuItemWidget_qt(QString name, vector<QString> values)
	{

	}
	virtual ~OptionMenuItemWidget_qt()
	{
		delete name;
		delete values;
	}

	virtual void setPos(double x, double y)
	{

	}
	virtual void moveBy(double x, double y)
	{

	}

	virtual void show()
	{
		name->show();
		values->show();
	}
	virtual void hide()
	{
		name->hide();
		values->hide();
	}
	virtual void addToPage(UiPageViewQt* page)
	{
		name->addToPage(page);
		values->addToPage(page);
	}

private:
	UiMenuItemWidget_qt *name;
	UiMenuItemMultiValWidget_qt *values;
	double item_spacing;
};

class OptionMenuWidget_qt: public UiPageMenuWidget_qt
{
public:
	OptionMenuWidget_qt(vector<OptionItem> *model)
	{
		menu_item_base_x = GameConfig::playground_view_width/2-150;
		menu_item_base_y = GameConfig::playground_view_height/2+100;

		for(auto model_item: *model)
		{
			auto item = new UiMenuItemWidget_qt(model_item.name);
			append_item(item);
		}

		selection_box = new UiPageMenuItemSelectioBoxWidget_qt(menu_items[0]->pos(),
				menu_width, menu_items[0]->height());

		//alignRight();
		alignCenter();
	}

};

OptionsMenu::OptionsMenu(vector<OptionItem> *model)
: model(model)
{
	vector<QString> names;
	for (auto item: *model)
	{
		actions.push_back(item.action);
	}
	last_item_index = this->actions.size()-1;
	//current_item_idx = start_index;

	view = new OptionMenuWidget_qt(model);

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
