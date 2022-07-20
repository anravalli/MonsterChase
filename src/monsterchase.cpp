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

#include "editor/level_editor.h"
#include "monsterchase.h"
#include "monsterchase_mainpage.h"
#include "gamecontroller.h"
#include "options_panel/optionpage_controller.h"

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

    qDebug("------- OPTION MENU -------");
    options_panel = new OptionPageController(this);

    qDebug("------- MATCH MENU -------");
    match_menu = populate_match_menu();

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

UiPageMenu *MonsterChase::populate_match_menu()
{

	game_controller = new GameController(this); //game_controller will be leaked on exit

	//This string array will be passed the menu widget to build the view, representing the model shared with the controller
	vector<QString> model = {"Start Match", "Player: andrea","Match Type: hunter","Back"};

	//This array of function objects to the menu controller to implement the actions associated to each menu entry
	vector<function<void()>> actions;

	//Start Match action: start the match
	actions.push_back([this]{
		this->page_view->hide();
		QApplication::instance()->removeEventFilter(this);
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
		this->back_to_main_menu();
		this->current_menu->show();
	});

	auto menu = new UiPageMenu(actions, model);
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
		this->back_to_main_menu();
	});

	auto *popup_view = new UiPagePopupWidget_qt(QString("Are you sure you want to exit?"),
			new UiPageMenuWidget_qt(&popup_model));

	auto exit_menu = new UiPageMenu(popup_actions, popup_view, 1);
	exit_menu->setPos(GameConfig::playground_width/2, GameConfig::playground_height/2);
	exit_menu->hide();
	exit_menu->addToPage(page_view);

	return exit_menu;
}

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

	void next_value_for(unsigned int idx)
	{
		auto item = dynamic_cast<UiMenuItemMultiValWidget_qt *>(menu_items[idx]);
		if(item != nullptr)
		{
			item->next();
		}
		return;
	}

	void previous_value_for(unsigned int idx)
	{
		auto item = dynamic_cast<UiMenuItemMultiValWidget_qt *>(menu_items[idx]);
		if(item != nullptr)
		{
			item->previous();
		}
		return;
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

UiPageMenu *MonsterChase::populate_match_selection_menu()
{
	vector<QString> popup_model = {"no match", "hunter",
			"survivor", "the dark hunt", "alone in the dark"};
	auto *popup_view = new UiPagePopupWidget_qt(QString("Select the match type:"),
			new SelectionMenuWidget_qt(popup_model));

	vector<function<void()>> popup_actions;
	popup_actions.push_back([this, popup_view]{
		this->game_controller->set_match_type(mt_alone_in_the_dark);
		return;
	});
	popup_actions.push_back([this]{
		this->current_menu->hide();
		this->current_menu = this->match_menu;
		this->current_menu->activate();
	});

	auto menu = new UiPageMenu(popup_actions, popup_view, 0);
	menu->setPos(GameConfig::playground_width/2, GameConfig::playground_height/2);
	menu->hide();
	menu->addToPage(page_view);
	//menu->setAlignement(align_center);

	return menu;
}

UiPageMenu *MonsterChase::populate_player_selection_menu()
{
	vector<QString> popup_model = {"Andrea", "Marco", "[new player]"};
	vector<function<void()>> popup_actions;
	popup_actions.push_back([this]{;});
	popup_actions.push_back([this]{
		this->current_menu->hide();
		this->current_menu = this->match_menu;
		this->current_menu->activate();
	});

	auto *popup_view = new UiPagePopupWidget_qt(QString("Select your player:"),
			new SelectionMenuWidget_qt(popup_model));

	auto menu = new UiPageMenu(popup_actions, popup_view, 0);
	menu->setPos(GameConfig::playground_width/2, GameConfig::playground_height/2);
	menu->hide();
	menu->addToPage(page_view);
	//menu->setAlignement(align_center);

	return menu;
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
    case Qt::Key_S:
    case Qt::Key_Down:
    case Qt::Key_Enter:
    case Qt::Key_Return:
    	ret = current_menu->handleKey(key, released);
    	break;
    case Qt::Key_Exit:
    case Qt::Key_Escape:
    	if (released)
    	{
    		if(current_menu == confirm_exit_menu)
    		{
    			back_to_main_menu();
    		}
    		else if(current_menu == base_menu)
    		{
    			open_popup(confirm_exit_menu);
    		}
    		else
    		{
    			back_to_main_menu();
    			this->current_menu->show();
    		}
    	}
        ret = true;
        break;
    case Qt::Key_A:
    case Qt::Key_Left:
    	if(current_menu == match_selection_menu or current_menu == match_selection_menu)
    	{
    		qDebug("<<< updating player or match");
    	}
    	ret = true;
    	break;
    case Qt::Key_D:
    case Qt::Key_Right:
    	if(current_menu == match_selection_menu or current_menu == match_selection_menu)
    	{
    		qDebug(">>> updating player or match");
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

void MonsterChase::back_to_main_menu()
{
	this->current_menu->hide();
	this->current_menu = this->base_menu;
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
}


