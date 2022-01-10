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


#include <editor/editor_ui.h>
#include "ui_editor.h"
#include "ui/uiviewitems_qt.h"

EditorUi::EditorUi(UiPageViewQt *parent) :
	UiPageViewQt(parent),
	ui(new Ui::editor)
{
	ui->setupUi(&ui_host);

	connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(close_editor()));
}

EditorUi::~EditorUi()
{
    delete ui;
}

void EditorUi::close_editor()
{
	qDebug("close editor");
	ui_host.hide();
	main_window->layout()->removeWidget(&ui_host);
	main_window->layout()->addWidget(view);

	hide();
	emit(editor_closed());
}

void EditorUi::setUpView()
{
    view->setBackgroundBrush(QPixmap(":/resources/textured-stainless-steel-sheet.jpg"));
    main_window->layout()->removeWidget(view);
    //main_window->layout()->setMenuBar(new QMenuBar());
    main_window->layout()->addWidget(&ui_host);
    ui->horizontalLayout->replaceWidget(ui->map_frame, view);
    //ui->horizontalLayout->setMenuBar(new QMenuBar());
}

