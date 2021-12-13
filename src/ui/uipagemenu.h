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

using namespace std;

//class UiMenuModel
//{
//public:
//	vector<string> model;
//};

class UiPageViewQt;

class UiPageMenu: QObject
{
    Q_OBJECT
public:
    UiPageMenu(vector<function<void()>> actions, vector<QString> model);
    void addToPage(UiPageViewQt* page);
    bool handleKey(int key, bool released);

protected:
    void select_next_item(bool released);
    void select_previous_item(bool released);
    void show_selcted_item(bool released);

private:
    vector<function<void()>> actions;
    vector<QString> model;
    int current_item_idx = 0;
    int last_item_index = 0;
    QTimer key_outo_repeat;

    QGraphicsSimpleTextItem view;

};

#endif // UIPAGEMENU_H
