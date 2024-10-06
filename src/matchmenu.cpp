/*
 *	Monster Chase: a testing playground for behaviors trees
 *
 *	Copyright 2022 Andrea Ravalli <anravalli @ gmail.com>
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
 *
 *  matchmenu.cpp: created on: 8 ago 2022
*/

#include "matchmenu.h"
#include <audio_server/AudioServer.h>
/*
 * MatchMenu methods
 */
MatchMenu::MatchMenu(vector<function<void()> > actions,
		UiPageAbstractMenuWidget *view) :
		UiPageMenu(actions, view, 0) {
}

void MatchMenu::on_match_type_changed(MatchType new_match) {
	qDebug("new_match: %d", new_match);
	match_type = new_match;
	int match_item_idx = 2;
	QString type(match_type_tostr(new_match));
	view->set_item_label(match_item_idx, QString("Match Type: ") + type);
	this->setAlignement(align_center);
}

void MatchMenu::on_player_name_changed(QString new_name) {
	qDebug("new_name: %s", new_name.toStdString().c_str());
	profile = new_name;
	int name_item_idx = 1;
	view->set_item_label(name_item_idx, QString("Player: ") + new_name);
	this->setAlignement(align_center);
}

/*
 * MatchMenuWidget_qt methods
 */
double MatchMenuWidget_qt::set_item_label(int item_idx,
		QString new_label) {
	menu_items[item_idx]->set_label(new_label);
	double new_item_width = menu_items[item_idx]->width();
	if (new_item_width > menu_width)
		selection_box->grow_by(new_item_width - menu_width);

	return 0;
}

/*
 * MatchPlayerSelectionMenu methods
 */
void MatchPlayerSelectionMenu::next_value_for(unsigned int idx) {
	((PopupSelectionMenuWidget_qt*) (this->view))->select_next_for(idx);
	return;
}

void MatchPlayerSelectionMenu::previous_value_for(unsigned int idx) {
	((PopupSelectionMenuWidget_qt*) (this->view))->select_prev_for(idx);
	return;
}

/*
 * PopupSelectionMenuWidget_qt methods
 */
PopupSelectionMenuWidget_qt::PopupSelectionMenuWidget_qt(QString info,
		UiPageMenuWidget_qt *menu) :
		UiPagePopupWidget_qt(info, menu) {
	qDebug("menu: %p", menu);
}

void PopupSelectionMenuWidget_qt::select_prev_for(int idx) {
	qDebug("menu: %p", this->menu);
	((SelectionMenuWidget_qt*) (this->menu))->previous_value_for(idx);
}

void PopupSelectionMenuWidget_qt::select_next_for(int idx) {
	((SelectionMenuWidget_qt*) (this->menu))->next_value_for(idx);
}

/*
 * SelectionMenuWidget_qt methods
 */
SelectionMenuWidget_qt::SelectionMenuWidget_qt(vector<QString> model) {
	UiAbstractMenuItemWidget *item;
	item = new UiMenuItemMultiValWidget_qt(model);
	append_item(item);
	item = new UiMenuItemWidget_qt("Back");
	append_item(item);
	selection_box = new UiPageMenuItemSelectioBoxWidget_qt(menu_items[0]->pos(),
			menu_width, menu_items[0]->height());
	pli_beep = AudioServer::instance().addToPlaylist(":/resources/audio/beep.wav");
}

QString SelectionMenuWidget_qt::get_item_label(int item_idx) {
	return menu_items[item_idx]->get_label();
}


double SelectionMenuWidget_qt::set_item_label(int item_idx,
		QString new_label) {
	menu_items[item_idx]->set_label(new_label);
	return menu_items[item_idx]->width();
}

void SelectionMenuWidget_qt::next_value_for(unsigned int idx) {
	auto item = dynamic_cast<UiMenuItemMultiValWidget_qt*>(menu_items[idx]);
	if (item != nullptr) {
		item->next();
		update_and_realign(item->width());
	}
	AudioServer::instance().play(pli_beep);
	return;
}

void SelectionMenuWidget_qt::previous_value_for(unsigned int idx) {
	auto item = dynamic_cast<UiMenuItemMultiValWidget_qt*>(menu_items[idx]);
	if (item != nullptr) {
		item->previous();
		update_and_realign(item->width());
	}
	AudioServer::instance().play(pli_beep);
	return;
}

void SelectionMenuWidget_qt::update_and_realign(double item_width) {
	qDebug("SelectionMenuWidget_qt::update_and_realign");
	qDebug(
			"+++ item_width: %f > this->menu_width: %f", item_width, this->menu_width)
			;
	if (item_width > this->menu_width)
		this->menu_width = item_width;

	if (item_width != this->menu_width)
		this->alignCenter();
}

int SelectionMenuWidget_qt::get_current_value_of(unsigned int idx) {
	int val = -1;
	auto item = dynamic_cast<UiMenuItemMultiValWidget_qt*>(menu_items[idx]);
	if (item != nullptr) {
		val = item->get_current();
	}
	return val;
}

void SelectionMenuWidget_qt::change_current_value_of(
		unsigned int item_idx, unsigned int val_idx) {
	auto item = dynamic_cast<UiMenuItemMultiValWidget_qt*>(menu_items[item_idx]);
	if (item != nullptr) {
		item->set_current(val_idx);
	}
	return;
}


