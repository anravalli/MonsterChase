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

#include "uipagemenu.h"
#include "ui/uipageview_qt.h"
#include "gameconfig.h"

UiPageMenu::UiPageMenu(vector<function<void()>> actions, vector<QString> model):
		actions(actions), model(model)
{
	QFont font("Helvetica",14,QFont::Bold);
	view.setFont(font);
	view.setPen(QPen(QColor(Qt::darkRed)));
	view.setBrush(QBrush(QColor(Qt::red)));
	view.setText(this->model[0]);
	view.setPos(GameConfig::playground_view_width/2-150,
			GameConfig::playground_view_height/2+100);
	view.show();
}

bool UiPageMenu::handleKey(int key, bool released){
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
    default:
        break;
    }
    return ret;
}

void UiPageMenu::select_next_item(bool released)
{
//    qDebug("select_next_item - released: %d", released);
    if(current_item_idx < last_item_index)
        current_item_idx++;
    if(released)
        key_outo_repeat.stop();
}

void UiPageMenu::select_previous_item(bool released)
{
//    qDebug("select_previous_item - released: %d", released);
    if(current_item_idx > 0)
        current_item_idx--;
    if(released)
        key_outo_repeat.stop();
}

void UiPageMenu::show_selcted_item(bool released)
{
    //qDebug("show_selcted_item - released: %d", released);
    if(released)
    {
        actions[current_item_idx]();
    }
}

void UiPageMenu::addToPage(UiPageViewQt* page)
{
    page->addItem(&(this->view));
}

//void UiPageMenu::show(){
//
//    view.show();
//}
