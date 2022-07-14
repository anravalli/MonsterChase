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
    auto game_controller = new GameController(this); //game_controller will be leaked on exit
    qDebug("------- OOPTION MENU -------");
    options_panel = new OptionPageController(this);

    //This string array will be passed the menu widget to build the view, representing the model shared with the controller
    vector<QString> model = {"Start Game","Options","High Scores","Editor","EXIT"};

    //This array of function objects to the menu controller to implement the actions associated to each menu entry
    vector<function<void()>> actions;

    //Start Game action: move to the match and profile selection page
    actions.push_back([this, game_controller]{
    	this->page_view->hide();
    	QApplication::instance()->removeEventFilter(this);
    	game_controller->show();
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
    	this->open_exit_popup();
    });
    qDebug("------- BASE MENU -------");
    base_menu = new UiPageMenu(actions, model);

    vector<QString> popup_model = {"yes", "not"};
    vector<function<void()>> popup_actions;
    popup_actions.push_back([this]{this->exit();});
    popup_actions.push_back([this]{
    	this->close_exit_popup();
    });
    qDebug("------- EXIT MENU -------");
    auto *popup_view = new UiPagePopupWidget_qt(QString("Are you sure you want to exit?"),
    		new UiPageMenuWidget_qt(&popup_model));

    confirm_exit_menu = new UiPageMenu(popup_actions, popup_view, 1);
    confirm_exit_menu->hide();
    confirm_exit_menu->addToPage(page_view);

    current_menu = base_menu;
    current_menu->addToPage(page_view);
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
    			close_exit_popup();
    		}
    		else{
    			open_exit_popup();
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

void MonsterChase::close_exit_popup()
{
	this->current_menu->hide();
	this->current_menu = this->base_menu;
	this->current_menu->activate();
}

void MonsterChase::open_exit_popup()
{
	this->current_menu->deactivate();
	this->current_menu = this->confirm_exit_menu;
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


