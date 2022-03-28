#ifndef UIPAGEMENUWIDGETS_QT_H
#define UIPAGEMENUWIDGETS_QT_H

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

#include <vector>

#include <ui_framework/uipageview_qt.h>
#include <gameconfig.h>

using namespace std;

class QGraphicsRectItem;
class QGraphicsSimpleTextItem;

#define MENU_ROW_OFFSET 35

class UiPageAbstractMenu
{
public:
	virtual void show() = 0;
	virtual void hide() = 0;
	virtual void activate() = 0;
	virtual void deactivate() = 0;

	virtual void addToPage(UiPageViewQt* page) = 0;
	virtual void selectionChanged(int index) = 0;
	virtual void setPos(double x, double y) = 0;
};

class UiPageMenuWidget_qt: public UiPageAbstractMenu
{
public:
	UiPageMenuWidget_qt(vector<QString> *model);
    virtual ~UiPageMenuWidget_qt();

    virtual void show() override final;
    virtual void hide() override final;
	virtual void activate() override final;
	virtual void deactivate() override final;

    virtual void addToPage(UiPageViewQt* page) override final;
    virtual void selectionChanged(int index) override final;
	virtual void setPos(double x, double y) override final;

private:
    double selection_box_base_x = 0;
    double selection_box_base_y = 0;
    QGraphicsRectItem *selection_box;
    double menu_item_base_x;
    double menu_item_base_y;
    vector<QGraphicsSimpleTextItem *> menu_items;
    //vector<QString> *model;
};

/*
 * UiPagePopupWidget_qt decorate a UiPageMenuWidget_qt with a popup window
 */
class UiPagePopupWidget_qt: public UiPageAbstractMenu
{
public:
	UiPagePopupWidget_qt(QString info, UiPageMenuWidget_qt *menu);
	virtual ~UiPagePopupWidget_qt();

	virtual void show() override final;
	virtual void hide() override final;
	virtual void activate() override final;
	virtual void deactivate() override final;

	virtual void addToPage(UiPageViewQt* page) override final;
	virtual void selectionChanged(int index) override final;
	virtual void setPos(double x, double y) override final;

private:
	QGraphicsSimpleTextItem *info;
	QGraphicsRectItem *drop;
	UiPageMenuWidget_qt *menu;
};


#endif // UIPAGEMENUWIDGETS_QT_H
