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

#include <iostream>

#include "editor/level_editor.h"
#include "monsterchase.h"
#include "monsterchase_mainpage.h"
#include "gamecontroller.h"

#include "options_panel/optionpage_controller.h"
#include "matchmenu.h"
#include "hiscore_panel/hiscorepage_controller.h"
#include "match.h"

#include <QGraphicsPixmapItem>
/*
 * Here we will build all the game objects responsible for the
 * game business logic, including the UI pages and game controllers.
 */

MonsterChase::MonsterChase():
    UiPageController(nullptr)
{
    initPageView<MonsterChaseMainPage>();

    qDebug("------- BASE MENU -------");
    base_menu = populate_base_menu();

    qDebug("------- MATCH MENU -------");
    match_menu = populate_match_menu();

    qDebug("------- OPTION MENU -------");
    options_panel = new OptionPageController(this);

    qDebug("------- HIGH SCORE PAGE -------");
    hiscore_panel = new HighScorePageController(this);

    qDebug("------- EXIT MENU -------");
    confirm_exit_menu = populate_confirm_exit_menu();

    current_menu = base_menu;
    current_menu->addToPage(page_view);
}

UiPageMenu *MonsterChase::populate_base_menu()
{
	//auto game_controller = new GameController(this); //game_controller will be leaked on exit

	//This string array will be passed the menu widget to build the view, representing the model shared with the controller
	vector<QString> model = {"Start Game","Options","High Scores","Editor","EXIT"};

	//This array of function objects to the menu controller to implement the actions associated to each menu entry
	vector<function<void()>> actions;

	//Start Game action: move to the match and profile selection page
	actions.push_back([this]{
		this->current_menu->deactivate();
		this->current_menu->hide();
		this->current_menu = this->match_menu;
		this->current_menu->show();
	});

	//Option action: move the option page
	actions.push_back([this]{
		this->open_options_panel();
	});

	//High Score action: move to high score page
	actions.push_back([this]{
		this->open_high_score_page();
	});

	//Editor action: open up the level editor
	actions.push_back([this]{
		this->open_level_editor();
	});

	//Exit action: open the exit confirmation popup
	actions.push_back([this]{
		this->open_popup(confirm_exit_menu);
	});

	auto menu = new UiPageMenu(actions, model);
	menu->setPos(GameConfig::playground_width/2,
			GameConfig::playground_width/2+100);
	menu->setAlignement(MenuAlignement::align_center);

	return menu;
}

UiPageMenu *MonsterChase::populate_match_selection_menu()
{
	vector<QString> popup_model = {"no match", "hunter",
			"survivor", "the dark hunt", "alone in the dark"};
	vector<function<void()>> popup_actions;

	auto *popup_view = new PopupSelectionMenuWidget_qt(QString("Select the match type:"),
			new SelectionMenuWidget_qt(popup_model));

	MatchPlayerSelectionMenu * menu = new MatchPlayerSelectionMenu(popup_actions, popup_view);

	popup_actions.push_back([this, menu, popup_view]{
		int i = menu->get_current_item_idx();
		//QString new_match = (popup_view->get_inner_menu())->get_item_label(i);
		int new_match = ((SelectionMenuWidget_qt *)(popup_view->get_inner_menu()))->get_current_value_of(i);

		std::cout << "item #"<< menu->get_current_item_idx() << " \"" << match_type_tostr((MatchType)new_match) <<"\" (" << new_match << ") selected" << std::endl;

		//menu->setAlignement(align_center);

		emit menu->match_changed((MatchType)new_match);
		//back
		back_to_menu(match_menu);
		return;
	});
	popup_actions.push_back([this]{
		back_to_menu(match_menu);
	});
	menu->set_actions(popup_actions);

	menu->setPos(GameConfig::playground_width/2, GameConfig::playground_height/2);
	menu->hide();
	menu->addToPage(page_view);
	menu->setAlignement(align_center);

	return menu;
}

UiPageMenu *MonsterChase::populate_player_selection_menu()
{

	vector<QString> popup_model = {"Andrea", "Marco", "[new player]"};
	vector<function<void()>> popup_actions;

	auto *popup_view = new PopupSelectionMenuWidget_qt(QString("Select your player:"),
			new SelectionMenuWidget_qt(popup_model));

	MatchPlayerSelectionMenu * menu = new MatchPlayerSelectionMenu(popup_actions, popup_view, 0);

	popup_actions.push_back([this, menu, popup_view]{
		std::cout << "menu ptr: "<< menu << std::endl;
		int i = menu->get_current_item_idx();
		QString new_name = (popup_view->get_inner_menu())->get_item_label(i);
		int v = ((SelectionMenuWidget_qt *)(popup_view->get_inner_menu()))->get_current_value_of(i);

		std::cout << "item #"<< menu->get_current_item_idx() << " \"" << new_name.toStdString() <<"\" (" << v << ") selected" << std::endl;
		//menu->setAlignement(align_center);

		emit menu->name_changed(new_name);
		//back
		back_to_menu(match_menu);
	});
	popup_actions.push_back([this]{
		back_to_menu(match_menu);
	});
	menu->set_actions(popup_actions);

	menu->setPos(GameConfig::playground_width/2, GameConfig::playground_height/2);
	menu->hide();
	menu->addToPage(page_view);
	menu->setAlignement(align_center);

	return menu;
}

UiPageMenu *MonsterChase::populate_match_menu()
{

	game_controller = new GameController(this); //game_controller will be leaked on exit

	//This string array will be passed the menu widget to build the view, representing the model shared with the controller
	vector<QString> model = {"Start Match", "Player: andrea","Match Type: hunter","Back"};

	//This array of function objects to the menu controller to implement the actions associated to each menu entry
	vector<function<void()>> actions;

	auto view = new MatchMenuWidget_qt(&model);
	auto menu = new MatchMenu(actions, view);

	//Start Match action: start the match
	actions.push_back([this, menu]{
		this->page_view->hide();
		QApplication::instance()->removeEventFilter(this);

		auto new_match = matchFactory(menu->get_match_type(), menu->get_profile());
		this->game_controller->set_match(new_match);
		this->game_controller->show();
	});

	//Player action: select the player
	this->player_selection_menu = populate_player_selection_menu();
	actions.push_back([this]{
		this->open_popup(this->player_selection_menu);
		return;
	});

	//Match Type Score action: select the match type
	this->match_selection_menu = populate_match_selection_menu();
	actions.push_back([this]{
		this->open_popup(this->match_selection_menu);
	});

	//Back action: go back to main menu
	actions.push_back([this]{
		this->back_to_menu(this->base_menu);
		this->current_menu->show();
	});
	menu->set_actions(actions);

	//TODO: check connection
	connect((MatchPlayerSelectionMenu *)player_selection_menu, SIGNAL(name_changed(QString)),
			menu, SLOT(on_player_name_changed(QString)));
	connect((MatchPlayerSelectionMenu *)match_selection_menu, SIGNAL(match_changed(MatchType)),
			menu, SLOT(on_match_type_changed(MatchType)));


	menu->setPos(GameConfig::playground_width/2,
			GameConfig::playground_width/2+100);
	menu->setAlignement(MenuAlignement::align_center);
	menu->addToPage(page_view);
	menu->hide();
	return menu;

}

UiPageMenu *MonsterChase::populate_confirm_exit_menu()
{
	vector<QString> popup_model = {"yes", "not"};
	vector<function<void()>> popup_actions;
	popup_actions.push_back([this]{this->exit();});
	popup_actions.push_back([this]{
		this->back_to_menu(this->base_menu);
	});

	auto *popup_view = new UiPagePopupWidget_qt(QString("Are you sure you want to exit?"),
			new UiPageMenuWidget_qt(&popup_model));

	auto exit_menu = new UiPageMenu(popup_actions, popup_view, 1);
	exit_menu->setPos(GameConfig::playground_width/2, GameConfig::playground_height/2);
	exit_menu->hide();
	exit_menu->addToPage(page_view);

	return exit_menu;
}

MonsterChase::~MonsterChase()
{
	current_menu = nullptr;
	delete confirm_exit_menu;
	delete base_menu;
}

bool MonsterChase::handleKey(int key, bool released)
{
	bool ret = false;
	switch(key){
	case Qt::Key_Up:
	case Qt::Key_W:
//	case Qt::Key_A:
//	case Qt::Key_Left:
//	case Qt::Key_D:
//	case Qt::Key_Right:
	case Qt::Key_S:
	case Qt::Key_Down:
	case Qt::Key_Enter:
	case Qt::Key_Return:
		ret = current_menu->handleKey(key, released);
		break;
	case Qt::Key_A:
	case Qt::Key_Left:
		if(((current_menu == match_selection_menu) or (current_menu == player_selection_menu)) and released)
		{
			qDebug("<<< updating player or match");
			int i = current_menu->get_current_item_idx();
			//((PopupSelectionMenuWidget_qt *)current_menu)->select_prev(i); //TODO: to be implemented
			((MatchPlayerSelectionMenu *)current_menu)->previous_value_for(i);
		}
		ret = true;
		break;
	case Qt::Key_D:
	case Qt::Key_Right:
		if(((current_menu == match_selection_menu) or (current_menu == player_selection_menu)) and released)
		{
			qDebug(">>> updating player or match");
			int i = current_menu->get_current_item_idx();
			//((PopupSelectionMenuWidget_qt *)current_menu)->select_next(i);  //TODO: to be implemented
			((MatchPlayerSelectionMenu *)current_menu)->next_value_for(i);
			//((UiPagePopupWidget_qt *)current_menu)->get_inner_menu();

		}
		ret = true;
		break;
	case Qt::Key_Exit:
	case Qt::Key_Escape:
		if (released)
		{
			if(current_menu == confirm_exit_menu)
			{
				back_to_menu(this->base_menu);
			}
			else if(current_menu == base_menu)
			{
				open_popup(confirm_exit_menu);
			}
			else if((current_menu == match_selection_menu) or (current_menu == player_selection_menu))
			{
				back_to_menu(this->match_menu);
			}
			else
			{
				back_to_menu(this->base_menu);
				this->current_menu->show();
			}
		}
		ret = true;
		break;
	default:
		break;
	}
	return ret;
}

void MonsterChase::exit()
{
    qDebug("MonsterChase::exit()");
    QApplication::instance()->exit();
}

void MonsterChase::back_to_menu(UiPageMenu *menu)
{
	this->current_menu->hide();
	this->current_menu = menu;
	this->current_menu->activate();
}

void MonsterChase::open_popup(UiPageMenu *popup)
{
	this->current_menu->deactivate();
	this->current_menu = popup;
	this->current_menu->show();
}

void MonsterChase::open_level_editor()
{
	this->page_view->hide();
	this->current_menu->deactivate();
	QApplication::instance()->removeEventFilter(this);

	level_editor = new LevelEditor::LevelEditor(this);
	level_editor->show();
	connect(level_editor, SIGNAL(editor_finalized()),this,SLOT(editor_closed()));
}

void MonsterChase::editor_closed()
{
	qDebug("MonsterChase::editor_closed()");
	this->current_menu->activate();
	UiPageController::show();
	delete level_editor;
}

void MonsterChase::open_options_panel()
{
	this->page_view->hide();
	QApplication::instance()->removeEventFilter(this);
	options_panel->show();
}

void MonsterChase::open_high_score_page()
{
	this->page_view->hide();
	QApplication::instance()->removeEventFilter(this);
	hiscore_panel->show();

}


