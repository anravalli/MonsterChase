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
		qDebug("item name: %s", name.toStdString().c_str());
		this->name = new UiMenuItemWidget_qt(name);
		qDebug("item values - size: %d; at [0]: %s", values.size(), values[0].toStdString().c_str());
		this->values = new UiMenuItemMultiValWidget_qt(values);
		this->_height = this->name->height();
		this->_width = this->name->width() + item_spacing + this->values->width();
	}
	virtual ~OptionMenuItemWidget_qt()
	{
		delete name;
		delete values;
	}

	virtual void setPos(double x, double y) override final
	{
		this->name->setPos(x, y);
		int offset = this->name->width() + item_spacing;
		this->values->setPos(x + offset, y);
		this->_pos = this->name->pos();
	}
	virtual void moveBy(double x, double y) override final
	{
		this->name->moveBy(x, y);
		this->values->moveBy(x, y);
	}

	virtual void show() override final
	{
		name->show();
		values->show();
	}
	virtual void hide() override final
	{
		name->hide();
		values->hide();
	}
	virtual void addToPage(UiPageViewQt* page) override final
	{
		name->addToPage(page);
		values->addToPage(page);
	}

private:
	UiMenuItemWidget_qt *name;
	UiMenuItemMultiValWidget_qt *values;
	double item_spacing = 20; //ixels between option name and value field
};

class OptionMenuWidget_qt: public UiPageMenuWidget_qt
{
public:
	OptionMenuWidget_qt(vector<OptionItem> *model)
	{
		menu_item_base_x = GameConfig::playground_width/2-150;
		menu_item_base_y = GameConfig::playground_width/2+100;

		for(auto model_item: *model)
		{
			qDebug("item name: %s", model_item.name.toStdString().c_str());
			UiAbstractMenuItemWidget *item;
			if(model_item.values.size())
				item = new OptionMenuItemWidget_qt(model_item.name, model_item.values);
			else
				item = new UiMenuItemWidget_qt(model_item.name);
			append_item(item);
			qDebug("menu width: %.02f", this->menu_width);
		}

		selection_box = new UiPageMenuItemSelectioBoxWidget_qt(menu_items[0]->pos(),
				menu_width, menu_items[0]->height());
		qDebug("GameConfig::playground_view_width/2: %.02f",GameConfig::playground_width/2);
		qDebug("this->menu_width/2: %.02f",this->menu_width/2);
		qDebug("menu position (x,y): %.02f, %.02f", GameConfig::playground_width/2-this->menu_width/2, menu_item_base_y);
		setPos(GameConfig::playground_width/2-this->menu_width/2, menu_item_base_y);
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
