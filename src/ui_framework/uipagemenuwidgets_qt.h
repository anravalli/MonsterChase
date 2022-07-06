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

//#define MENU_ROW_OFFSET 35

enum MenuAlignement {
	align_left,
	align_center,
	align_right
};

class UiPageAbstractMenuWidget
{
public:
	virtual void show() = 0;
	virtual void hide() = 0;
	virtual void activate() = 0;
	virtual void deactivate() = 0;

	virtual void addToPage(UiPageViewQt* page) = 0;
	virtual void selectionChanged(int index) = 0;
	virtual void setPos(double x, double y) = 0;
	virtual void setAlignement(MenuAlignement a) = 0;
};

class UiPageMenuItemSelectioBoxWidget_qt
{
public:
	UiPageMenuItemSelectioBoxWidget_qt(QPointF initial_pos, double inner_w,
			double inner_h);
	void show();
	void hide();
	void resetToPos(double new_x, double new_y);
	void selectItemAt(int index, double spacing = 1);
	void addToPage(UiPageViewQt* page);

private:
	QGraphicsRectItem *selection_box;
	double x;
	double y;
	double inner_width;
	double inner_height;

	double menu_item_height = 0;
	int selection_box_border_width = 15;
	int selection_box_border_heigth = 5;
};

class UiPageMenuWidget_qt: public UiPageAbstractMenuWidget
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
	virtual void setAlignement(MenuAlignement a) override final;

private:
	MenuAlignement alignement = align_left;

    UiPageMenuItemSelectioBoxWidget_qt *selection_box;
    double item_vertical_spacing_factor = 1.5;
    double menu_item_height = 0;
    double menu_item_base_x;
    double menu_item_base_y;
    double menu_width = 0;
    double menu_height = 0;
    vector<QGraphicsSimpleTextItem *> menu_items;
    //vector<QString> *model;
    void alignRight();
    void alignLeft();
    void alignCenter();
};

/*
 * UiPagePopupWidget_qt decorate a UiPageMenuWidget_qt with a popup window
 */
class UiPagePopupWidget_qt: public UiPageAbstractMenuWidget
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
	virtual void setAlignement(MenuAlignement a) override final;

private:
    double item_vertical_spacing_factor = 1.5;
	QGraphicsSimpleTextItem *info;
	QGraphicsRectItem *drop;
	UiPageMenuWidget_qt *menu;
};

#endif // UIPAGEMENUWIDGETS_QT_H
