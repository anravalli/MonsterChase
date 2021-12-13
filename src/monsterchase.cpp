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
#include "ui/uipageview_qt.h"
#include "gamecontroller.h"

#include <QGraphicsPixmapItem>
/*
 * Here we will build all the game objects responsible for the
 * game business logic, including the UI pages and game controllers.
 */

MonsterChase::MonsterChase():
    UiPageController(nullptr)
{
    initPageView<UiPageViewQt>();
    auto game_controller = new GameController(this); //game_controller will be leaked on exit
    function<void()> a = [this, game_controller]{
    	this->page_view->hide();
    	QApplication::instance()->removeEventFilter(this);
    	game_controller->show();
    };
    vector<function<void()>> actions;
    actions.push_back(a);
    actions.push_back([this]{this->exit();});

    vector<QString> model;
    model.push_back("Press ENTER to start");
    model.push_back("EXIT");

    menu = new UiPageMenu(actions, model);
    menu->addToPage(page_view);

    logo = new QGraphicsPixmapItem(QPixmap(":/resources/monster_chase_logo.png"));
    page_view->addItem(logo);
}


MonsterChase::~MonsterChase()
{
	delete menu;
}

bool MonsterChase::handleKey(int key, bool released){
    bool ret = false;
    switch(key){
    case Qt::Key_Up:
    case Qt::Key_W:
    case Qt::Key_S:
    case Qt::Key_Down:
    case Qt::Key_Enter:
    case Qt::Key_Return:
    	ret = menu->handleKey(key, released);
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

//void MonsterChase::select_next_item(bool released)
//{
////    qDebug("select_next_item - released: %d", released);
//    if(current_item_idx < last_item_index)
//        current_item_idx++;
//    if(released)
//        key_outo_repeat.stop();
//}
//
//void MonsterChase::select_previous_item(bool released)
//{
////    qDebug("select_previous_item - released: %d", released);
//    if(current_item_idx > 0)
//        current_item_idx--;
//    if(released)
//        key_outo_repeat.stop();
//}
//
//void MonsterChase::show_selcted_item(bool released)
//{
//    //qDebug("show_selcted_item - released: %d", released);
//    if(released)
//    {
//        page_view->hide();
//        QApplication::instance()->removeEventFilter(this);
//        actions[current_item_idx]();
//    }
//}
