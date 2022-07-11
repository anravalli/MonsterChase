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
#include <QtWidgets>
#include "uipagemenuwidgets_qt.h"

UiPageAbstractMenuWidget::~UiPageAbstractMenuWidget() {};
UiAbstractMenuItemWidget::~UiAbstractMenuItemWidget() {};

double UiAbstractMenuItemWidget::height()
{
	return this->_height;
}

double UiAbstractMenuItemWidget::width()
{
	return this->_width;
}

QPointF UiAbstractMenuItemWidget::pos()
{
	return this->_pos;
}

UiPageMenuWidget_qt::UiPageMenuWidget_qt(vector<QString> *model)
{

	menu_item_base_x = GameConfig::playground_view_width/2-150;
	menu_item_base_y = GameConfig::playground_view_height/2+100;

	for(auto model_item: *model)
	{
		auto item = new UiMenuItemWidget_qt(model_item);
		append_item(item);
	}

	selection_box = new UiPageMenuItemSelectioBoxWidget_qt(menu_items[0]->pos(),
			menu_width, menu_items[0]->height());

	//alignRight();
	alignCenter();
};

void UiPageMenuWidget_qt::append_item(UiAbstractMenuItemWidget *item)
{
	menu_items.push_back(item);
	int offset = (menu_items.size()-1) * item->height()*item_vertical_spacing_factor;

	double item_witdh = item->width();
	menu_width = menu_width > item_witdh ? menu_width : item_witdh;

	item->setPos(menu_item_base_x, menu_item_base_y+offset);

	menu_height += offset;
}


UiPageMenuWidget_qt::~UiPageMenuWidget_qt()
{
	for(auto item: menu_items)
		delete item;
};

void UiPageMenuWidget_qt::show()
{
	selection_box->show();
	for(auto item: menu_items)
		item->show();
}

void UiPageMenuWidget_qt::hide()
{
	selection_box->hide();
	for(auto item: menu_items)
		item->hide();
}

void UiPageMenuWidget_qt::activate()
{
	selection_box->show();
}

void UiPageMenuWidget_qt::deactivate()
{
	selection_box->hide();
}

void UiPageMenuWidget_qt::addToPage(UiPageViewQt* page)
{
	selection_box->addToPage(page);
	for(auto item: menu_items)
		item->addToPage(page);
}

void UiPageMenuWidget_qt::selectionChanged(int index)
{
	selection_box->selectItemAt(index, item_vertical_spacing_factor);
}

void UiPageMenuWidget_qt::setPos(double x, double y)
{
	int offset = 0;

	selection_box->resetToPos(x,y);
	for(auto item: menu_items)
	{
		item->setPos(x,y+offset);
		offset += item->height() * item_vertical_spacing_factor;
	}
}

void UiPageMenuWidget_qt::setAlignement(MenuAlignement a)
{
	alignement = a;
	switch(alignement)
	{
	case align_left:
		this->alignLeft();
		break;
	case align_center:
		this->alignCenter();
		break;
	case align_right:
		this->alignRight();
		break;
	default:
		break;
	}
	return;
}

void UiPageMenuWidget_qt::alignRight()
{

	double dx = 0;
	for(auto item: menu_items)
	{
		dx = menu_width - item->width();
		item->moveBy(dx, 0);
	}
}
void UiPageMenuWidget_qt::alignLeft()
{

	double dx = 0;
	for(auto item: menu_items)
	{
		dx =item->width()-menu_width;
		item->moveBy(dx, 0);
	}
}
void UiPageMenuWidget_qt::alignCenter()
{
	double dx = 0;
	for(auto item: menu_items)
	{
		dx = (menu_width - item->width())/2;
		item->moveBy(dx, 0);
	}
}

/*
 * UiPagePopupWidget_qt methods
 */
UiPagePopupWidget_qt::UiPagePopupWidget_qt(QString info, UiPageMenuWidget_qt *menu):
		menu(menu)
{
	QFont font("Helvetica",14,QFont::Bold);
	double border_width = 15;

	double base_pos_x = GameConfig::playground_width/2;
	double base_pos_y = GameConfig::playground_height/2;

	this->info = new QGraphicsSimpleTextItem(info);
	this->info->setFont(font);
	this->info->setPen(QPen(QColor(Qt::darkRed)));
	this->info->setBrush(QBrush(QColor(Qt::red)));

	double info_w = this->info->boundingRect().width();
	double info_h = this->info->boundingRect().height();

	this->info->setPos(base_pos_x-info_w/2,
			base_pos_y-(info_w+border_width*2)/2+info_h);
	this->info->hide();

//	qDebug("base_pos: %f, %f", base_pos_x, base_pos_y);
//	qDebug("info_w: %f; info_h %f", info_w, info_h);
//	qDebug("drop pos: %f, %f", base_pos_x-((info_w+30)/2), base_pos_y-(info_w+30)/2);
	this->drop = new QGraphicsRectItem(
			base_pos_x-((info_w+border_width*2)/2),
			base_pos_y-(info_w+border_width*2)/2,
			info_w+border_width*2,
			info_h * item_vertical_spacing_factor * 4
			);
	this->drop->setBrush(QBrush(QColor(0xD7,0xD7,0xD7,0x80)));
	this->drop->setPen(QPen(QBrush(QColor(0xFF,0xD7,0xD7,0xFF)), 2, Qt::PenStyle::SolidLine));
	this->drop->hide();

	this->menu->setPos(this->info->x()+info_w/2-30, this->info->y()+50);
	this->menu->hide();
}

UiPagePopupWidget_qt::~UiPagePopupWidget_qt()
{
	delete info;
	delete drop;
	delete menu;
}

void UiPagePopupWidget_qt::addToPage(UiPageViewQt* page)
{
	page->addItem(drop);
	page->addItem(info);
	menu->addToPage(page);
}

void UiPagePopupWidget_qt::show()
{
	drop->show();
	info->show();
	menu->show();
}

void UiPagePopupWidget_qt::hide()
{
	drop->hide();
	info->hide();
	menu->hide();
}

void UiPagePopupWidget_qt::activate()
{
	menu->activate();
}

void UiPagePopupWidget_qt::deactivate()
{
	menu->deactivate();
}

void UiPagePopupWidget_qt::selectionChanged(int index)
{
	menu->selectionChanged(index);
}

void UiPagePopupWidget_qt::setPos(double x, double y)
{
	QPointF current_pos = drop->pos();
	double delta_x = x - current_pos.x();
	double delta_y = y - current_pos.y();
	drop->moveBy(delta_x, delta_y);
	info->moveBy(delta_x, delta_y);
	menu->setPos(delta_x, delta_y);
}


void UiPagePopupWidget_qt::setAlignement(MenuAlignement a)
{
	menu->setAlignement(a);
}

UiPageMenuItemSelectioBoxWidget_qt::UiPageMenuItemSelectioBoxWidget_qt(
		QPointF initial_pos, double inner_w, double inner_h) :
		inner_width(inner_w), inner_height(inner_h)
{
	x = initial_pos.x() - selection_box_border_width;
	y = initial_pos.y() - selection_box_border_heigth;
	selection_box = new QGraphicsRectItem(x, y,
			inner_width + selection_box_border_width * 2,
			inner_height + selection_box_border_heigth * 2);
	x=0; //Workaround to cope with "mysterious" QGraphicsRectItem.setPos() behavior
	y=0; //Workaround to cope with "mysterious" QGraphicsRectItem.setPos() behavior
	selection_box->setBrush(QBrush(QColor(0xFF, 0xD7, 0x00, 0x80)));
	selection_box->setPen(QPen(Qt::PenStyle::NoPen));
}

void UiPageMenuItemSelectioBoxWidget_qt::show()
{
	selection_box->show();
}

void UiPageMenuItemSelectioBoxWidget_qt::hide()
{
	selection_box->hide();
}

void UiPageMenuItemSelectioBoxWidget_qt::resetToPos(double new_x, double new_y)
{
	x = new_x - selection_box->rect().topLeft().x()
			- selection_box_border_width;
	y = new_y - selection_box->rect().topLeft().y()
			- selection_box_border_heigth;
	selection_box->setPos(x, y);
}

void UiPageMenuItemSelectioBoxWidget_qt::selectItemAt(int index,
		double spacing) {
	selection_box->setPos(x, y + inner_height * spacing * index);
}

void UiPageMenuItemSelectioBoxWidget_qt::addToPage(UiPageViewQt* page)
{
	page->addItem(selection_box);
}

UiMenuItemWidget_qt::UiMenuItemWidget_qt(QString label)
{
	_label = new QGraphicsSimpleTextItem();
	QFont font("Helvetica",14,QFont::Bold);

	_label->setFont(font);
	_label->setPen(QPen(QColor(Qt::darkRed)));
	_label->setBrush(QBrush(QColor(Qt::red)));
	_label->setText(label);

	_width = _label->boundingRect().width();
	_height = _label->boundingRect().height();
}

void UiMenuItemWidget_qt::setPos(double x, double y)
{
	this->_pos.setX(x);
	this->_pos.setY(y);
	this->_label->setPos(_pos);
}

void UiMenuItemWidget_qt::moveBy(double x, double y)
{
	this->_pos.setX(_pos.x()+x);
	this->_pos.setY(_pos.y()+y);
	this->_label->moveBy(x, y);
}

void UiMenuItemWidget_qt::show()
{
	this->_label->show();
}

void UiMenuItemWidget_qt::hide()
{
	this->_label->hide();
}

void UiMenuItemWidget_qt::addToPage(UiPageViewQt *page)
{
	page->addItem(this->_label);
}

UiMenuItemWidget_qt::~UiMenuItemWidget_qt()
{
}

UiMenuItemMultiValWidget_qt::UiMenuItemMultiValWidget_qt(vector<QString> values):
		UiMenuItemWidget_qt(values[0]), _values(values)
{
}

UiMenuItemMultiValWidget_qt::~UiMenuItemMultiValWidget_qt()
{
}

void UiMenuItemMultiValWidget_qt::next()
{
	unsigned int idx = current_idx;
	unsigned int max = _values.size()-1;
	if (++idx > max) idx = max;

	set_current(idx);
}

void UiMenuItemMultiValWidget_qt::previous()
{
	//unsigned int idx = current_idx;
	//if (--idx < 0) idx = 0;

	set_current(--current_idx);
}

int UiMenuItemMultiValWidget_qt::get_current()
{
	return current_idx;
}

void UiMenuItemMultiValWidget_qt::set_current(unsigned int idx)
{
	if(idx>=_values.size()) return;

	current_idx = idx;

	QString pre_label("< ");
	QString post_label(" >");
	if (idx == 0)
		pre_label = "  ";
	if (idx == _values.size()-1)
		post_label = "  ";
	_label->setText(pre_label + _values[current_idx] + post_label);
}
