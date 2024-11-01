/*
 * OptionsMenu.cpp
 *
 *  Created on: 12 giu 2022
 *      Author: andrea
 */

#include "optionsmenu.h"
#include <ui_framework/uipagemenuwidgets_qt.h>
#include <audio_server/AudioServer.h>

class OptionMenuItemWidget_qt: public UiAbstractMenuItemWidget
{
public:
	OptionMenuItemWidget_qt(QString name, vector<QString> values)
	{
		this->name = new UiMenuItemWidget_qt(name);
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

	virtual void removeFromPage(UiPageViewQt* page) override final
	{
		name->removeFromPage(page);
		values->removeFromPage(page);
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
		pli_beep = AudioServer::instance().addFx(":/resources/audio/beep.wav");
		for(auto model_item: *model)
		{
			UiAbstractMenuItemWidget *item;
			if(model_item.str_values.size())
				item = new OptionMenuItemWidget_qt(model_item.name, model_item.str_values);
			else
				item = new UiMenuItemWidget_qt(model_item.name);
			append_item(item);
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
		AudioServer::instance().playFx(pli_beep);
		return;
	}

	void previous_value_for(unsigned int idx)
	{
		auto item = dynamic_cast<OptionMenuItemWidget_qt *>(menu_items[idx]);
		if(item != nullptr)
		{
			item->previous_value();
		}
		AudioServer::instance().playFx(pli_beep);
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
		UiPageMenuWidget_qt::alignCenter();

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

	view = new OptionMenuWidget_qt(model);

}

OptionsMenu::~OptionsMenu()
{
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
        run_item_action(released);
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


void OptionsMenu::run_item_action(bool released)
{
	if((*model)[current_item_idx].default_idx < 0)
	{
		UiPageMenu::run_item_action(released);
	}
}

void OptionsMenu::select_next_value(bool released)
{
    if(!released) return;

    ((OptionMenuWidget_qt *)view)->next_value_for(current_item_idx);
    if(released)
    {
        //key_auto_repeat.stop();
        actions[current_item_idx]();
    }
}

void OptionsMenu::select_previous_value(bool released)
{
    if(!released) return;

    ((OptionMenuWidget_qt *)view)->previous_value_for(current_item_idx);
    if(released)
    {
    	//key_auto_repeat.stop();
    	actions[current_item_idx]();
    }
}

int OptionsMenu::get_current_value_of(int idx)
{
	return ((OptionMenuWidget_qt *)view)->get_current_value_of(idx);
}

void OptionsMenu::change_current_value_of(int item_idx, int val_idx)
{
	((OptionMenuWidget_qt *)view)->change_current_value_of(item_idx, val_idx);
}

