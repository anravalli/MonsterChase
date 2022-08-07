/*
 * optionpage_controller.cpp
 *
 *  Created on: 24 mar 2022
 *      Author: andrea
 */

#include "hiscorepage_controller.h"

#include "hiscorepage_view.h"
#include "optionsmenu.h"

HighScorePageController::HighScorePageController(UiPageController *parent):
	UiPageController(parent)
{

	//is_saved = true;
	initPageView<HiscorePageView>();




	//options_menu->addToPage(page_view);
}

HighScorePageController::~HighScorePageController()
{
	// TODO Auto-generated destructor stub
}

void HighScorePageController::show(){
	//load saved config
	//update config model
    UiPageController::show();
}

void HighScorePageController::exit()
{
    qDebug("OptionPageController::exit()");
    //qDebug("is_saved %d", is_saved);
    UiPageController::exit();
}

bool HighScorePageController::handleKey(int key, bool released)
{

    bool ret = false;
    switch(key){
    case Qt::Key_W:
    	//move down
    case Qt::Key_S:
    	//move up
    case Qt::Key_A:
    	//select previous score group
    	//--> change label
    	//--> update score table
    case Qt::Key_D:
    	//select next score group
    case Qt::Key_Up:
    case Qt::Key_Down:
    case Qt::Key_Left:
    case Qt::Key_Right:
    case Qt::Key_Enter:
    case Qt::Key_Return:
    	//ret = active_menu->handleKey(key, released);
    	break;
    case Qt::Key_Exit:
    case Qt::Key_Escape:
    	if (released)
    	{
    		exit();
    	}
        ret = true;
        break;
    default:
        break;
    }
    return ret;

}

