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

#include "uipageview_qt.h"
#include "uiviewitems_qt.h"

#include "gameconfig.h"

UiPageViewQt::UiPageViewQt(UiPageViewQt *parent)
{
    Q_UNUSED(parent);

    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, GameConfig::playground_width, GameConfig::playground_width);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    if(parent == nullptr)
    {
    	main_window = new QWidget();

    	view = new UiBaseQGraphicsView(scene);
    	view->setRenderHint(QPainter::Antialiasing);
    	view->setCacheMode(QGraphicsView::CacheBackground);
    	view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    	view->setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Monster Chase"));

    	auto *layout = new QVBoxLayout();
    	layout->setSizeConstraint(QLayout::SetFixedSize);
    	layout->addWidget(view);
    	main_window->setLayout(layout);
    }
    else
    {
        view = parent->getView();
        main_window = parent->getMainWindow();
    }
}

UiPageViewQt::~UiPageViewQt()
{
    delete view; //it should be reference counted to avoid crash on exit!
    delete scene;
}

UiBaseQGraphicsView *UiPageViewQt::getView() const
{
    return view;
}

QWidget *UiPageViewQt::getMainWindow() const
{
		return main_window;
}

double UiPageViewQt::width()
{
    return scene->sceneRect().width();
}

double UiPageViewQt::height()
{
    return scene->sceneRect().height();
}

void UiPageViewQt::show()
{
    view->setScene(scene);
    setUpView();
    view->show();
    main_window->show();
}

void UiPageViewQt::hide()
{
    //using a NULL scene here, instead of the QWidget inherited hide() method,
    //seems to fix the rendering issues related the page change.
    view->setScene(nullptr);
}

void UiPageViewQt::addItem(QGraphicsItem *item)
{
    scene->addItem(item);
}

void UiPageViewQt::removeItem(QGraphicsItem *item)
{
    scene->removeItem(item);
}


void UiPageViewQt::setUpView()
{
    view->setBackgroundBrush(QColor(Qt::darkGray));
};
