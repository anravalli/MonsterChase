/*
 * matchmenu.h
 *
 *  Created on: 25 lug 2022
 *      Author: andrea
 */

#ifndef SRC_MATCHMENU_H_
#define SRC_MATCHMENU_H_

#include <ui_framework/uipagemenu.h>
#include <ui_framework/uipagemenuwidgets_qt.h>

class SelectionMenuWidget_qt: public UiPageMenuWidget_qt
{
public:
	SelectionMenuWidget_qt(vector<QString> model)
	{
		UiAbstractMenuItemWidget *item;
		item = new UiMenuItemMultiValWidget_qt(model);
		append_item(item);
		item = new UiMenuItemWidget_qt("Back");
		append_item(item);
		selection_box = new UiPageMenuItemSelectioBoxWidget_qt(menu_items[0]->pos(),
				menu_width, menu_items[0]->height());

	}

	virtual QString get_item_label(int item_idx) override final
	{
		return menu_items[item_idx]->get_label();
	}

	virtual double set_item_label(int item_idx, QString new_label) override final
	{
		menu_items[item_idx]->set_label(new_label);
		return menu_items[item_idx]->width();
	}

	void next_value_for(unsigned int idx)
	{
		auto item = dynamic_cast<UiMenuItemMultiValWidget_qt *>(menu_items[idx]);
		if(item != nullptr)
		{
			item->next();
			update_and_realign(item->width());
		}
		return;
	}

	void previous_value_for(unsigned int idx)
	{
		auto item = dynamic_cast<UiMenuItemMultiValWidget_qt *>(menu_items[idx]);
		if(item != nullptr)
		{
			item->previous();
			update_and_realign(item->width());
		}
		return;
	}

	void update_and_realign(double item_width)
	{
		qDebug("SelectionMenuWidget_qt::update_and_realign");
		qDebug("+++ item_width: %f > this->menu_width: %f", item_width, this->menu_width);
		if (item_width > this->menu_width)	this->menu_width = item_width;
		if (item_width != this->menu_width)	this->alignCenter();

	}

	int get_current_value_of(unsigned int idx)
	{
		int val = -1;
		auto item = dynamic_cast<UiMenuItemMultiValWidget_qt *>(menu_items[idx]);
		if(item != nullptr)
		{
			val = item->get_current();
		}
		return val;
	}

	void change_current_value_of(unsigned int item_idx, unsigned int val_idx)
	{
		auto item = dynamic_cast<UiMenuItemMultiValWidget_qt *>(menu_items[item_idx]);
		if(item != nullptr)
		{
			item->set_current(val_idx);
		}
		return;
	}
};


class PopupSelectionMenuWidget_qt: public UiPagePopupWidget_qt
{
public:
	PopupSelectionMenuWidget_qt(QString info, UiPageMenuWidget_qt *menu):
		UiPagePopupWidget_qt(info, menu)
	{
		qDebug("menu: %p", menu);
	}

	void select_prev_for(int idx)
	{
		qDebug("menu: %p", this->menu);
		((SelectionMenuWidget_qt *)this->menu)->previous_value_for(idx);
	}

	void select_next_for(int idx)
	{
		((SelectionMenuWidget_qt *)this->menu)->next_value_for(idx);
	}
};


class MatchPlayerSelectionMenu: public UiPageMenu
{
	Q_OBJECT
public:
	MatchPlayerSelectionMenu(vector<function<void()>> actions, UiPageAbstractMenuWidget *view, int start_index = 0):
		UiPageMenu(actions, view, start_index){};
public:
	void next_value_for(unsigned int idx)
	{
		((PopupSelectionMenuWidget_qt *)this->view)->select_next_for(idx);
		return;
	}

	void previous_value_for(unsigned int idx)
	{
		((PopupSelectionMenuWidget_qt *)this->view)->select_prev_for(idx);
		return;
	}
signals:
	void name_changed(QString new_name);
	void match_changed(QString new_match);
};


class MatchMenu: public UiPageMenu
{
	Q_OBJECT
public:
	MatchMenu(vector<function<void()>> actions, UiPageAbstractMenuWidget *view):
		UiPageMenu(actions, view, 0)
	{

	}

	virtual ~MatchMenu(){};
	public slots:
		void on_player_name_changed(QString new_name)
		{
			qDebug("new_name: %s", new_name.toStdString().c_str());
			int name_item_idx = 1;
			view->set_item_label(name_item_idx, QString("Player: ")+new_name);
			this->setAlignement(align_center);
		}
		void on_match_type_changed(QString new_match)
		{
			qDebug("new_match: %s", new_match.toStdString().c_str());
			int match_item_idx = 2;
			view->set_item_label(match_item_idx, QString("Match Type: ")+new_match);


			this->setAlignement(align_center);
		}
	private:
};

class MatchMenuWidget_qt: public UiPageMenuWidget_qt
{
public:
	MatchMenuWidget_qt(vector<QString> *model): UiPageMenuWidget_qt(model){}
	virtual double set_item_label(int item_idx, QString new_label) override final
	{
		menu_items[item_idx]->set_label(new_label);
		double new_item_width =  menu_items[item_idx]->width();
		if(new_item_width > menu_width)
			selection_box->grow_by(new_item_width - menu_width);
		return 0;
	}

};




#endif /* SRC_MATCHMENU_H_ */
