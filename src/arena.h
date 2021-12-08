#ifndef ARENA_H
#define ARENA_H

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

#include <QGraphicsItem>
#include <QFile>
#include <QTextStream>
#include "game_entity.h"

#define MAP_WIDTH 100
#define MAP_HEIGHT 100

enum BrickType {
    none,
    standard,
    cap_up,
    cap_dw,
    cap_lx,
    cap_rx,
    throwable
};

class UiPageViewQt;

class Brick: public QGraphicsRectItem
{
public:
    Brick(QRectF br_shape);

    void setIndex(std::pair<int,int> idx);
private:
    std::pair<int,int> _idx;
};

class Arena: public QObject, public GameEntityI
{
    Q_OBJECT

signals:
    void build_complete();

public:
    Arena(double brick_width);
    Arena(QString fname, double brick_width);

    void show() override;
    void hide() override;
    virtual void addToPage(UiPageViewQt* page) override;
    bool mapComplete();

    virtual Brick *getBrick(std::pair<int, int> idx);

    QPointF idxToPos(int ix, int iy);
    std::pair<int, int> posToIdx(QPointF pos);

public slots:
    void showNextBrick();

private:
    char bin_map[MAP_HEIGHT][MAP_WIDTH];
    Brick* map[MAP_HEIGHT][MAP_WIDTH];

    int brick_count = 0;
    bool completion_status = false;
    QTimer* timer = nullptr;

    double map_cell_w = 0;
    double map_cell_h = 0;
    Brick* addBrick(std::pair<int,int> idx);

};

#endif // ARENA_H

