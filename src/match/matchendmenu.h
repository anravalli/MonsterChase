/*
 * matchendmenu.h
 *
 *  Created on: 31 ott 2022
 *      Author: andrea
 */

#ifndef SRC_MATCHENDMENU_H_
#define SRC_MATCHENDMENU_H_

#include <lib/ui_framework/uipagemenu.h>

class MatchEndPopup: public UiPageMenu
{
public:
	MatchEndPopup(vector<function<void()>> actions, UiPageAbstractMenuWidget *view, int start_index):
		UiPageMenu(actions, view, start_index){}

	virtual bool handleKey(int key, bool released) override final {
	    bool ret = false;
	    switch(key){
	    case Qt::Key_Enter:
	    case Qt::Key_Return:
	        run_item_action(released);
	        ret = true;
	        break;
	    default:
	        break;
	    }
	    return ret;
	}
};


#endif /* SRC_MATCHENDMENU_H_ */
