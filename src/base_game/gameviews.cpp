/*
 *	Monster Chase: a testing playground for behaviors trees
 *
 *	Copyright 2021 Andrea Ravalli <anravalli @ gmail.com>
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


#include <lib/ui_framework/uiviewitems_qt.h>
#include "gameviews.h"

GamePage::GamePage(UiPageViewQt *parent):
    UiPageViewQt(parent)
{
}

void GamePage::setUpView()
{
    view->setBackgroundBrush(QPixmap(":/resources/textured-stainless-steel-sheet.jpg"));
}

PlayTime::PlayTime()
    :color(255,127,127)
{
    QFont font("Helvetica",14,QFont::Bold);
    this->setFont(font);
    this->setPen(QPen(color));
}

void PlayTime::setTime(int time){
    this->setText(QString::asprintf("%04d", time));
    return;
}

