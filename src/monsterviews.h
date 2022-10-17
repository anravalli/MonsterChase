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

#ifndef MONSTERVIEWS_H
#define MONSTERVIEWS_H

#include "monster.h"

#include <QtWidgets>
#include <QGraphicsItem>

class UiPageViewQt;

namespace Monster {

class MonsterShape;
class MonsterSight;
class MonsterView;
class MonsterEnergyGouge;

MonsterView *monsterViewFactory(MonsterType type, MonsterModel* model);

class MonsterView
{
    friend MonsterView* monsterViewFactory(MonsterType mtype, MonsterModel* model);

public:
    MonsterView(MonsterModel* m);
    virtual ~MonsterView();

    void show();
    void hide();
    void update();
    void updateGeometry(double x, double y, double scale, double direction);
    void setPosition(double x, double y);
    void setRotation(double dir);


    void addToPage(UiPageViewQt* page);
    void removeFromPage(UiPageViewQt* page);

protected:
    MonsterModel* model;
    MonsterShape* shape=nullptr;
    MonsterSight* sight=nullptr;
    MonsterEnergyGouge *energy_gouge=nullptr;
};


class MonsterShape : public QGraphicsItem
{
public:
    MonsterShape(MonsterModel* m);
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

protected:
    MonsterShape(){}
    QColor color[3];
    MonsterModel* model;
};

class MonsterSight : public QGraphicsItem
{
public:
    MonsterSight(MonsterModel* m)
        :model(m){}

    QRectF boundingRect() const Q_DECL_OVERRIDE;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

private:
    MonsterModel* model;
};


class MonsterEnergyGouge : public QGraphicsItem
{
public:
	MonsterEnergyGouge(MonsterModel* m)
        :model(m){}

    QRectF boundingRect() const Q_DECL_OVERRIDE;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

	bool isVisibilityToggle() const {
		return visibility_toggle;
	}

	void setVisibilityToggle(bool visibilityToggle = false) {
		visibility_toggle = visibilityToggle;
	}

private:
    MonsterModel* model;
    QRectF bbox;
    bool visibility_toggle = false;
};

class MonsterTriangularShape: public MonsterShape{
public:
    MonsterTriangularShape(MonsterModel* m);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;
};

}

#endif // MONSTERVIEWS_H
