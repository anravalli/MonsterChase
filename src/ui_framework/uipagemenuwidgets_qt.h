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

class UiAbstractMenuItemWidget
{
public:
	virtual ~UiAbstractMenuItemWidget() = 0;

	virtual void setPos(double x, double y) = 0;
	virtual void moveBy(double x, double y) = 0;
	virtual double height();
	virtual double width();
	virtual QPointF pos();
	virtual QPointF center_anchor();

	virtual void show() = 0;
	virtual void hide() = 0;
	virtual void addToPage(UiPageViewQt* page) = 0;

	virtual void set_label(QString new_label){Q_UNUSED(new_label);return;};
	virtual QString get_label(){return QString("");};
protected:
	QPointF _pos;
	double _height;
	double _width;
};

//required for decoration
class UiPageAbstractMenuWidget
{
public:
	virtual ~UiPageAbstractMenuWidget() = 0;

	virtual void show() = 0;
	virtual void hide() = 0;
	virtual void activate() = 0;
	virtual void deactivate() = 0;

	virtual void addToPage(UiPageViewQt* page) = 0;
	virtual void selectionChanged(int index) = 0;
	virtual void setPos(double x, double y) = 0;
	virtual void setAlignement(MenuAlignement a) = 0;
	virtual double height() = 0;
	virtual double width() = 0;
	virtual QPointF pos() = 0;

	virtual void set_item_label(int item_idx, QString new_label){Q_UNUSED(item_idx); Q_UNUSED(new_label);return;};
	virtual QString get_item_label(int item_idx){Q_UNUSED(item_idx); return QString("");};
	virtual void set_item_label(UiAbstractMenuItemWidget *item, QString new_label){Q_UNUSED(item); Q_UNUSED(new_label); return;};
	virtual QString get_item_label(UiAbstractMenuItemWidget *item){return item->get_label();};
};

class UiMenuItemWidget_qt: public UiAbstractMenuItemWidget
{
public:
	UiMenuItemWidget_qt(QString label);

	virtual void setPos(double x, double y) override final;
	virtual void moveBy(double x, double y) override final;

	virtual void show() override final;
	virtual void hide() override final;
	virtual void addToPage(UiPageViewQt* page) override final;

	virtual ~UiMenuItemWidget_qt();
protected:
	QGraphicsSimpleTextItem *_label;

};

class UiMenuItemMultiValWidget_qt: public UiMenuItemWidget_qt
{
public:
	UiMenuItemMultiValWidget_qt(vector<QString> values);

	virtual ~UiMenuItemMultiValWidget_qt();

	void next();
	void previous();
	int get_current();
	void set_current(unsigned int idx);
private:
	vector<QString> _values;
	unsigned int current_idx = 0;

};

class UiPageMenuItemSelectioBoxWidget_qt
{
public:
	UiPageMenuItemSelectioBoxWidget_qt(QPointF initial_pos, double inner_w,
			double inner_h);
	~UiPageMenuItemSelectioBoxWidget_qt();
	void show();
	void hide();
	void resetToPos(double new_x, double new_y);
	void selectItemAt(int index, double spacing = 1);
	void addToPage(UiPageViewQt* page);

	void grow_by(double dw);

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
	UiPageMenuWidget_qt(){};
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

	virtual double height() override final;
	virtual double width() override final;
	virtual QPointF pos() override final;
	void moveBy(double dx, double dy);
	void append_item(UiAbstractMenuItemWidget *item);

protected:
	MenuAlignement alignement = align_left;

    UiPageMenuItemSelectioBoxWidget_qt *selection_box;
    double item_vertical_spacing_factor = 1.5;
    double menu_item_base_x = 0;
    double menu_item_base_y = 0;
    double menu_width = 0;
    double menu_height = 0;
    vector<UiAbstractMenuItemWidget *> menu_items;

    virtual void alignRight();
    virtual void alignLeft();
    virtual void alignCenter();
};

/*
 * UiPagePopupWidget_qt decorate a UiPageMenuWidget_qt like a popup window
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

	virtual double height() override final;
	virtual double width() override final;
	virtual QPointF pos() override final;

	UiPageMenuWidget_qt* get_inner_menu() {
		return menu;
	}

private:
    double item_vertical_spacing_factor = 1.5;
protected:
	QGraphicsSimpleTextItem *info;
	QGraphicsRectItem *drop;
	UiPageMenuWidget_qt *menu;
};

#endif // UIPAGEMENUWIDGETS_QT_H
