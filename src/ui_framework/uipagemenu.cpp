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
#include "uipageview_qt.h"


UiPageMenu::UiPageMenu(vector<function<void()>> actions, vector<QString> model, int start_index):
        actions(actions)
{
	last_item_index = this->actions.size()-1;
	current_item_idx = start_index;

	view = new UiPageMenuWidget_qt(&model);
	view->show();
}

UiPageMenu::UiPageMenu(vector<function<void()>> actions, UiPageAbstractMenuWidget *view, int start_index):
        actions(actions), view(view)
{
	last_item_index = this->actions.size()-1;
	current_item_idx = start_index;
	this->view->show();
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
        run_item_action(released);
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
    if(!released) return;
	if(current_item_idx < last_item_index)
        current_item_idx++;
    view->selectionChanged(current_item_idx);
}

void UiPageMenu::select_previous_item(bool released)
{
	//    qDebug("select_previous_item - released: %d", released);
	if(!released) return;
	if(current_item_idx > 0)
		current_item_idx--;
	view->selectionChanged(current_item_idx);

}

void UiPageMenu::run_item_action(bool released)
{
    //qDebug("show_selcted_item - released: %d", released);
    if(released)
    {
        actions[current_item_idx]();
    }
}

void UiPageMenu::addToPage(UiPageViewQt* page)
{
   view->addToPage(page);
}

void UiPageMenu::removeFromPage(UiPageViewQt* page)
{
   view->removeFromPage(page);
}



