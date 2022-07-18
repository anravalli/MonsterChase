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
		qDebug("item values - size: %ld; at [0]: %s", values.size(), values[0].toStdString().c_str());
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

	virtual QPointF center_anchor()  override final
	{
		double anchor_x = this->_pos.x()+this->name->width() + item_spacing/2;
		return QPointF(anchor_x, this->_pos.y());
	}

	void next_value()
	{
		this->values->next();
	}

	void previous_value()
	{
		this->values->previous();
	}

	unsigned int get_current_value()
	{
		return this->values->get_current();
	}

	void change_current_value(unsigned int idx)
	{
		this->values->set_current(idx);
	}

private:
	UiMenuItemWidget_qt *name;
	UiMenuItemMultiValWidget_qt *values;
	double item_spacing = 20; //pixels between option name and value field
};

class OptionMenuWidget_qt: public UiPageMenuWidget_qt
{
public:
	OptionMenuWidget_qt(vector<OptionItem> *model)
	{
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

	}

	void next_value_for(unsigned int idx)
	{
		auto item = dynamic_cast<OptionMenuItemWidget_qt *>(menu_items[idx]);
		if(item != nullptr)
		{
			item->next_value();
		}
		return;
	}

	void previous_value_for(unsigned int idx)
	{
		auto item = dynamic_cast<OptionMenuItemWidget_qt *>(menu_items[idx]);
		if(item != nullptr)
		{
			item->previous_value();
		}
		return;
	}

	int get_current_value_of(unsigned int idx)
	{
		int val = -1;
		auto item = dynamic_cast<OptionMenuItemWidget_qt *>(menu_items[idx]);
		if(item != nullptr)
		{
			val = item->get_current_value();
		}
		return val;
	}

	void change_current_value_of(unsigned int item_idx, unsigned int val_idx)
	{
		auto item = dynamic_cast<OptionMenuItemWidget_qt *>(menu_items[item_idx]);
		if(item != nullptr)
		{
			item->change_current_value(val_idx);
		}
		return;
	}


	virtual void alignCenter() override
	{
		qDebug("OptionMenuWidget_qt::alignCenter");
		UiPageMenuWidget_qt::alignCenter();
/*
		double delta_width = 0;
		double delta_left = 0;
		double delta_right = 0;

		for(auto item: menu_items)
		{
			qDebug("+++ menu_item_base_x: %.02f; item.x(): %.02f", this->menu_item_base_x, item->pos().x());
			qDebug("+++ menu_width: %.02f; item->width: %.02f", this->menu_width, item->width());
			double delta_left_tmp = this->menu_item_base_x - item->pos().x();
			double delta_right_tmp = (item->pos().x() + item->width()) - (this->menu_item_base_x + this->menu_width);
			qDebug("+++ delta_left_tmp: %.02f; delta_right_tmp: %.02f", delta_left_tmp, delta_right_tmp);

			delta_left = delta_left > delta_left_tmp ? delta_left : delta_left_tmp;
			delta_right = delta_right > delta_right_tmp ? delta_right : delta_right_tmp;
			qDebug("+++ delta_left: %.02f; delta_right: %.02f", delta_left, delta_right);
		}
		delta_width = (delta_left > delta_right ? delta_left : delta_right) * 2;
		qDebug("+++ delta_width: %.02f", delta_width);
*/
		// target --> 60px (estimated)
		selection_box->grow_by(60);
	}

private:

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

bool OptionsMenu::handleKey(int key, bool released)
{
    bool ret = false;
    switch(key){
    case Qt::Key_Up:
    case Qt::Key_W:
        select_previous_item(released);
        ret = true;
        break;
    case Qt::Key_S:
    case Qt::Key_Down:
        select_next_item(released);
        ret = true;
        break;
    case Qt::Key_Enter:
    case Qt::Key_Return:
        show_selcted_item(released);
        ret = true;
        break;
    case Qt::Key_A:
    case Qt::Key_Left:
        select_previous_value(released);
        ret = true;
        break;
    case Qt::Key_D:
    case Qt::Key_Right:
        select_next_value(released);
        ret = true;
        break;
    case Qt::Key_Exit:
    case Qt::Key_Escape:
    default:
        break;
    }
    return ret;
}

void OptionsMenu::select_next_value(bool released)
{
//    qDebug("select_next_item - released: %d", released);
    if(!released) return;

    ((OptionMenuWidget_qt *)view)->next_value_for(current_item_idx);
    if(released)
        key_auto_repeat.stop();
}

void OptionsMenu::select_previous_value(bool released)
{
//    qDebug("select_next_item - released: %d", released);
    if(!released) return;

    ((OptionMenuWidget_qt *)view)->previous_value_for(current_item_idx);
    if(released)
        key_auto_repeat.stop();
}

