/*
 * optionpage_view.h
 *
 *  Created on: 28 mar 2022
 *      Author: andrea
 */

#ifndef SRC_OPTIONS_PANEL_OPTIONPAGE_VIEW_H_
#define SRC_OPTIONS_PANEL_OPTIONPAGE_VIEW_H_

#include <QtWidgets>

#include <ui_framework/uipageview_qt.h>

class OptionPageView: public UiPageViewQt {
public:
	OptionPageView(UiPageViewQt *parent);
	virtual ~OptionPageView();

protected:
    virtual void setUpView() override;
};

#endif /* SRC_OPTIONS_PANEL_OPTIONPAGE_VIEW_H_ */
