/*
 *	Monster Chase: a testing playground for behaviors trees
 *
 *	Copyright 2019 Andrea Ravalli <anravalli @ gmail.com>
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

#include "monsterchase.h"
#include "ui/uipage_qt.h"
#include "gamecontroller.h"

/*
 * Here we will build all the game objects responsible for the
 * game business logic, including the UI pages and game controllers.
 */

MonsterChase::MonsterChase():
    UiPageController(nullptr)
{
    UiPageController *game_controller = new GameController(this);
    items.push_back(game_controller);
}


MonsterChase::~MonsterChase()
{
    for(auto i: items)
        delete i;
}

bool MonsterChase::handleKey(int key, bool released){
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
    case Qt::Key_Exit:
    case Qt::Key_Escape:
        exit();
        ret = true;
        break;
    default:
        break;
    }
    return ret;
}

void MonsterChase::exit(){
    qDebug("MonsterChase::exit()");
    QApplication::instance()->exit();
}

void MonsterChase::show()
{
    QApplication::instance()->installEventFilter(this);
    page->show();
}

void MonsterChase::select_next_item(bool released)
{
//    qDebug("select_next_item - released: %d", released);
    if(current_item_idx < last_item_index)
        current_item_idx++;
    if(released)
        key_outo_repeat.stop();
}

void MonsterChase::select_previous_item(bool released)
{
//    qDebug("select_previous_item - released: %d", released);
    if(current_item_idx > 0)
        current_item_idx--;
    if(released)
        key_outo_repeat.stop();
}

void MonsterChase::show_selcted_item(bool released)
{
    //qDebug("show_selcted_item - released: %d", released);
    if(released)
    {
        page->hide();
        QApplication::instance()->removeEventFilter(this);
        items[current_item_idx]->show();
    }
}
