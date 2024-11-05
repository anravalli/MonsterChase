/*
 * optionpage_controller.cpp
 *
 *  Created on: 24 mar 2022
 *      Author: andrea
 */

#include "hiscorepage_controller.h"

#include "hiscorepage_view.h"
enum match_type
{
	hunter,
	survivor,
	the_dark_hunt,
	alone_in_the_dark
};
static void fill_empty_row(vector<vector<QString>> *model)
{
	for(int i=model->size(); i<10; i++)
	{
		model->push_back(vector<QString>{"","",""});
	}
}

HighScorePageController::HighScorePageController(UiPageController *parent):
	UiPageController(parent)
{
	initPageView<HiscorePageView>();

	high_scores[hunter].push_back(vector<QString>{"Andrea","75","2540"});
	fill_empty_row(&high_scores[hunter]);

	high_scores[survivor].push_back(vector<QString>{"Marco","543","15040"});
	fill_empty_row(&high_scores[survivor]);

	fill_empty_row(&high_scores[the_dark_hunt]);
	fill_empty_row(&high_scores[alone_in_the_dark]);

}

HighScorePageController::~HighScorePageController()
{
	// TODO Auto-generated destructor stub
}

void HighScorePageController::show(){
    UiPageController::show();
}

void HighScorePageController::exit()
{
    UiPageController::exit();
}

bool HighScorePageController::handleKey(int key, bool released)
{

	static bool toggle_exit_button = false;
    bool ret = false;
    switch(key){
    case Qt::Key_W:
    case Qt::Key_Down:
    	if(released)
    	{
    		toggle_exit_button = true;
    		((HiscorePageView *)page_view)->activate_exit_button(toggle_exit_button);
    	}
    	ret = true;
    	break;
    case Qt::Key_S:
    case Qt::Key_Up:
    	if(released)
    	{
    		toggle_exit_button = false;
    		((HiscorePageView *)page_view)->activate_exit_button(toggle_exit_button);
    	}
    	ret = true;
    	break;
    case Qt::Key_A:
    case Qt::Key_Left:
    	if(released)
    	{
    	//select previous score group
    		int table = ((HiscorePageView *)page_view)->previous_table();
    	//--> update score table
    		((HiscorePageView *)page_view)->update_score_table(&high_scores[table]);
    	}
    	ret = true;
    	break;
    case Qt::Key_D:
    case Qt::Key_Right:
    	if(released)
    	{
    	//select next score group
    		int table = ((HiscorePageView *)page_view)->next_table();
    	//--> update score table
    		((HiscorePageView *)page_view)->update_score_table(&high_scores[table]);
    	}
    	ret = true;
    	break;
    case Qt::Key_Enter:
    case Qt::Key_Return:
    	if(released and toggle_exit_button)
    	{
    		exit();
    		ret = true;
    	}
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

