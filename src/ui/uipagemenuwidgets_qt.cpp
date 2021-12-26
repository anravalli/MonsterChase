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

#include "uipagemenuwidgets_qt.h"

UiPageMenuWidget_qt::UiPageMenuWidget_qt(vector<QString> *model)
//	:model(model)
{
	QFont font("Helvetica",14,QFont::Bold);

	int offset = 0;
	menu_item_base_x = GameConfig::playground_view_width/2-150;
	menu_item_base_y = GameConfig::playground_view_height/2+100;
	for(auto model_item: *model)
	{
		auto item = new QGraphicsSimpleTextItem();
		item->setFont(font);
		item->setPen(QPen(QColor(Qt::darkRed)));
		item->setBrush(QBrush(QColor(Qt::red)));
		item->setText(model_item);
		item->setPos(menu_item_base_x, menu_item_base_y+offset);
		menu_items.push_back(item);

		offset += MENU_ROW_OFFSET;
	}
	double selection_box_x = menu_items[0]->pos().x()-15;
	double selection_box_y = menu_items[0]->pos().y()-5;
	qDebug("building selection_box at: %f,%f", selection_box_x,selection_box_y);
	selection_box = new QGraphicsRectItem(
			selection_box_x,
			selection_box_y,
			menu_items[0]->boundingRect().width()+30,
			menu_items[0]->boundingRect().height()+10);
	qDebug("selection_box position: %f,%f", selection_box->x(),selection_box->y());
	qDebug("selection_box rect position: %f,%f", selection_box->rect().topLeft().x(),selection_box->rect().topLeft().y());
	selection_box->setBrush(QBrush(QColor(0xFF,0xD7,0x00,0x80)));
	selection_box->setPen(QPen(Qt::PenStyle::NoPen));
};

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
	page->addItem(selection_box);
	for(auto item: menu_items)
		page->addItem(item);
}

void UiPageMenuWidget_qt::selectionChanged(int index)
{
	selection_box->setPos(selection_box_base_x, selection_box_base_y+MENU_ROW_OFFSET*index);
	qDebug(" -- selection_box position: %f,%f", selection_box->x(),selection_box->y());
	qDebug(" -- selection_box rect position: %f,%f", selection_box->rect().topLeft().x(),selection_box->rect().topLeft().y());
}

void UiPageMenuWidget_qt::setPos(double x, double y)
{
	int offset = 0;
	selection_box_base_x = x-selection_box->rect().topLeft().x()-15;
	selection_box_base_y = y-selection_box->rect().topLeft().y()-5;

	qDebug(" ++ new pos: %f,%f", x, y);
	qDebug(" ++ selection_box_base: %f,%f", selection_box_base_x, selection_box_base_y);

	selection_box->setPos(x,y);
	for(auto item: menu_items)
	{
		item->setPos(x,y+offset);
		offset += MENU_ROW_OFFSET;
	}
}

/*
 * UiPagePopupWidget_qt mthods
 */
UiPagePopupWidget_qt::UiPagePopupWidget_qt(QString info, UiPageMenuWidget_qt *menu):
		menu(menu)
{
	QFont font("Helvetica",14,QFont::Bold);
	double base_pos_x = GameConfig::playground_width/2;
	double base_pos_y = GameConfig::playground_height/2;

	this->info = new QGraphicsSimpleTextItem(info);
	this->info->setFont(font);
	this->info->setPen(QPen(QColor(Qt::darkRed)));
	this->info->setBrush(QBrush(QColor(Qt::red)));
	double info_w = this->info->boundingRect().width();
	//double info_h = this->info->boundingRect().height();
	this->info->setPos(base_pos_x-info_w/2, base_pos_y-(info_w+30)/2+15);
	this->info->hide();

//	qDebug("base_pos: %f, %f", base_pos_x, base_pos_y);
//	qDebug("info_w: %f; info_h %f", info_w, info_h);
//	qDebug("drop pos: %f, %f", base_pos_x-((info_w+30)/2), base_pos_y-(info_w+30)/2);
	this->drop = new QGraphicsRectItem(base_pos_x-((info_w+30)/2), base_pos_y-(info_w+30)/2,
			info_w+30,
			MENU_ROW_OFFSET*4);
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

