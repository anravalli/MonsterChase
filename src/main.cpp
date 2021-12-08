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

#include "monsterchase.h"
#include <QApplication>
#include "ui/uipageview_qt.h"

/*
 * Here we do just unix signal handling,
 * command line processing and game initialization
 */

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MonsterChase game;
    QWidget * main_window = new QWidget();

    QLayout * layout = new QVBoxLayout();
    UiPageViewQt *game_page = game.getPageView();
    QGraphicsView * view = (QGraphicsView *)(game_page->getView());

    layout->addWidget(view);
    main_window->setLayout(layout);

    game_page->hide();
    main_window->show();

    game.show();

    return a.exec();
}
