/*
 * optionpage_controller.cpp
 *
 *  Created on: 24 mar 2022
 *      Author: andrea
 */

#include "optionpage_controller.h"
#include "optionpage_view.h"
#include "optionsmenu.h"

OptionPageController::OptionPageController(UiPageController *parent):
	UiPageController(parent)
{

	is_saved = true;
	initPageView<OptionPageView>();


	model.push_back(
			OptionItem(
					"Screen Resolution",
					{"800x600","1024x768","1280x960"},
					0,
					0,
					[this]{	this->change_screen_resolution(); }
			)
	);

	model.push_back(
			OptionItem(
					"Fullscreen",
					{"yes", "not"},
					1,
					1,
					[this]{this->set_fullscreen();}
			)
	);

	model.push_back(
			OptionItem(
					"Sound",
					{"on","off"},
					0,
					0,
					[this]{this->set_sounds();}
			)
	);

	model.push_back(
			OptionItem(
					"Apply",
					{},
					-1,
					-1,
					[this]{this->apply_settings();}
			)
	);

	model.push_back(
			OptionItem(
					"Back",
					{},
					-1,
					-1,
					[this]{this->open_confirm_popup();}
			)
	);

	options_menu = new OptionsMenu(&model);
	options_menu->setPos(GameConfig::playground_width/2,
	    		GameConfig::playground_width/2+100);
	options_menu->setAlignement(align_center);

	vector<QString> popup_model = {"apply", "discard"};
	vector<function<void()>> popup_actions;
	popup_actions.push_back([this]{
		this->apply_settings();
		this->close_confirm_popup();
		this->exit();
	});
	popup_actions.push_back([this]{
		this->close_confirm_popup();
		this->exit();
	});
	auto *popup_view = new UiPagePopupWidget_qt(QString("Do you want to apply your changes before exit?"),
			new UiPageMenuWidget_qt(&popup_model));

	confirm_exit_menu = new UiPageMenu(popup_actions, popup_view, 1);
	confirm_exit_menu->setPos(GameConfig::playground_width/2, GameConfig::playground_height/3);
	confirm_exit_menu->hide();
	confirm_exit_menu->addToPage(page_view);

	active_menu = options_menu;
	active_menu->addToPage(page_view);
}

OptionPageController::~OptionPageController()
{
	// TODO Auto-generated destructor stub
}

void OptionPageController::show(){
	//load saved config
	//update config model
    UiPageController::show();
}

void OptionPageController::exit()
{
    qDebug("OptionPageController::exit()");
    qDebug("is_saved %d", is_saved);
    UiPageController::exit();
}

bool OptionPageController::handleKey(int key, bool released)
{

    bool ret = false;
    switch(key){
    case Qt::Key_W:
    case Qt::Key_S:
    case Qt::Key_A:
    case Qt::Key_D:
    case Qt::Key_Up:
    case Qt::Key_Down:
    case Qt::Key_Left:
    case Qt::Key_Right:
    case Qt::Key_Enter:
    case Qt::Key_Return:
    	ret = active_menu->handleKey(key, released);
    	break;
    case Qt::Key_Exit:
    case Qt::Key_Escape:
    	if (released)
    	{
    		if(active_menu == confirm_exit_menu)
    		{
    			close_confirm_popup();
    		}
    		else if (!is_saved)
    		{
    			open_confirm_popup();
    		}
    		else
    			exit();
    	}
        ret = true;
        break;
    default:
        break;
    }
    return ret;

}

void OptionPageController::open_confirm_popup()
{
	if (!is_saved)
	{
		this->active_menu->deactivate();
		this->active_menu = this->confirm_exit_menu;
		this->active_menu->show();
	}
	else
		this->exit();
}

void OptionPageController::close_confirm_popup()
{
	this->active_menu->hide();
	this->active_menu = this->options_menu;
	this->active_menu->activate();
}

void OptionPageController::change_screen_resolution()
{
	int idx = options_menu->get_current_item_idx();
	int val_idx = ((OptionsMenu *)options_menu)->get_current_value_of(idx);
	qDebug("screen resolution set to %s", model[idx].values[val_idx].toStdString().c_str());
	is_saved = false;
}

void OptionPageController::set_fullscreen()
{
	int idx = options_menu->get_current_item_idx();
	int val_idx = ((OptionsMenu *)options_menu)->get_current_value_of(idx);
	qDebug("fullscreen set to %s", model[idx].values[val_idx].toStdString().c_str());
	is_saved = false;
}

void OptionPageController::set_sounds()
{
	int idx = options_menu->get_current_item_idx();
	int val_idx = ((OptionsMenu *)options_menu)->get_current_value_of(idx);
	qDebug("sound set to %s", model[idx].values[val_idx].toStdString().c_str());
	is_saved = false;
}

void OptionPageController::apply_settings()
{
	is_saved = true;
}
