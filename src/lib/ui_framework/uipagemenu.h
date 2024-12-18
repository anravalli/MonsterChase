#ifndef UIPAGEMENU_H
#define UIPAGEMENU_H

/*
 *	Monster Chase: a testing playground for behaviors trees
 *
 *	Copyright 2021 Andrea Ravalli <anravalli @ gmail.com>
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
*/

#include <vector>
#include <functional>
#include <QTimer>
#include <QObject>
#include <QtWidgets>

#include "uipagemenuwidgets_qt.h"

using namespace std;

class UiPageViewQt;

class UiPageMenu: public QObject
{
    Q_OBJECT
public:
	UiPageMenu(){};
    UiPageMenu(vector<function<void()>> actions, vector<QString> model, int start_index = 0);
    UiPageMenu(vector<function<void()>> actions, UiPageAbstractMenuWidget *view, int start_index = 0);
    virtual void addToPage(UiPageViewQt* page);
    virtual void removeFromPage(UiPageViewQt* page);
    virtual bool handleKey(int key, bool released);
    virtual void setPos(double x, double y);
    virtual void show();
    virtual void hide();
    virtual void activate();
    virtual void deactivate();
    void setAlignement(MenuAlignement a);

	virtual ~UiPageMenu() {	}

	int get_current_item_idx() const
	{
		return current_item_idx;
	}

	void set_actions(const vector<function<void()> > &actions) {
		this->actions = actions;
		this->last_item_index = this->actions.size()-1;
	}

protected:
    void select_next_item(bool released);
    void select_previous_item(bool released);
    virtual void run_item_action(bool released);

    vector<function<void()>> actions;

    int current_item_idx = 0;
    int last_item_index = 0;
    //QTimer key_auto_repeat;

    UiPageAbstractMenuWidget *view = nullptr;

};

inline void UiPageMenu::setPos(double x, double y)
{
	view->setPos(x-view->width()/2, y);
}

inline void UiPageMenu::show()
{
	view->selectionChanged(current_item_idx);
	view->show();
}

inline void UiPageMenu::hide()
{
	view->hide();
}

inline void UiPageMenu::activate()
{
	view->activate();
}

inline void UiPageMenu::deactivate()
{
	view->deactivate();
}

inline void UiPageMenu::setAlignement(MenuAlignement a)
{
	view->setAlignement(a);
};

#endif // UIPAGEMENU_H
