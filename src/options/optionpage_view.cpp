/*
 * optionpage_view.cpp
 *
 *  Created on: 28 mar 2022
 *      Author: andrea
 */

#include "optionpage_view.h"

#include <lib/ui_framework/uiviewitems_qt.h>

OptionPageView::OptionPageView(UiPageViewQt *parent):
	UiPageViewQt(parent)
{
	auto logo = new QGraphicsPixmapItem(QPixmap(":/resources/monster_chase_logo.png"));
	logo->setScale(0.5);
	scene->addItem(logo);
}

OptionPageView::~OptionPageView()
{
	// TODO Auto-generated destructor stub
}

void OptionPageView::setUpView()
{
    view->setBackgroundBrush(QColor(0xff, 0x88, 0x16, 0xff));
    //view->setBackgroundBrush(QColor(0x8e,0x68,0x85,0xff));
}
