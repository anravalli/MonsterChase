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

#ifndef MONSTERCHASE_H
#define MONSTERCHASE_H

#include "ui/uipagecontroller.h"
#include "ui/uipagemenu.h"
#include <vector>
#include <functional>
#include <QTimer>

using namespace std;

class QGraphicsPixmapItem;

class MonsterChase : public UiPageController
{
    //Q_OBJECT

public:
    MonsterChase();
    ~MonsterChase() override ;
    void exit() override;
    bool handleKey(int key, bool released) override;

protected:
    void select_next_item(bool released);
    void select_previous_item(bool released);
    void show_selcted_item(bool released);

private:
    UiPageMenu *menu;
    QGraphicsPixmapItem *logo;
//    vector<function<void()>> actions;
//    int current_item_idx = 0;
//    int last_item_index = 0;
//    QTimer key_outo_repeat;
};


#endif // MONSTERCHASE_H
