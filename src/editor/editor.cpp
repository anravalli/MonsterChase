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


#include "editor.h"
#include "ui_editor.h"
#include "ui/uiviewitems_qt.h"

#include "../arena.h"
#include "../gameconfig.h"

editor::editor(UiPageViewQt *parent, QWidget *parent_widget) :
	UiPageViewQt(parent),
	ui(new Ui::editor),
	ui_parent(parent_widget)
{
	ui_parent->layout()->removeWidget(view);

	ui->setupUi(&ui_host);
	delete ui->map_view;
	ui->map_view = nullptr;

	ui_parent->layout()->addWidget(&ui_host);

	ui->horizontalLayout->replaceWidget(ui->map_frame, view);

	QString map = ":/resources/map.txt";
	arena = new Arena(map, GameConfig::playground_width/MAP_WIDTH);
	arena->addToPage(this);
	arena->showAll();

	connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(close_editor()));
}

editor::~editor()
{
	delete arena;
    delete ui;
}

void editor::close_editor()
{
	qDebug("close editor");
	ui_parent->layout()->removeWidget(&ui_host);
	ui_parent->layout()->addWidget(view);
	emit(editor_closed());
}

void editor::setUpView()
{
    view->setBackgroundBrush(QPixmap(":/resources/textured-stainless-steel-sheet.jpg"));
}

