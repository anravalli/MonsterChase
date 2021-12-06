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

#include "uipage_qt.h"
#include "uibase_qtview.h"

#include "gameconfig.h"

UiPageQt::UiPageQt(QWidget *parent)
{
    Q_UNUSED(parent);

    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, GameConfig::playground_width, GameConfig::playground_width);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    view = new UiBaseQtView(scene);
    view->setRenderHint(QPainter::Antialiasing);
    view->setBackgroundBrush(QPixmap(":/resources/textured-stainless-steel-sheet.jpg"));
    view->setCacheMode(QGraphicsView::CacheBackground);
    view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view->setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Monster Chase"));
}

UiPageQt::~UiPageQt()
{
    delete view;
    delete scene;
}

double UiPageQt::width()
{
    return scene->sceneRect().width();
}

double UiPageQt::height()
{
    return scene->sceneRect().height();
}

void UiPageQt::show()
{
    view->show();
}

void UiPageQt::addItem(QGraphicsItem *item)
{
    scene->addItem(item);
}
