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


#include "arena.h"
#include <assert.h>
#include <ui_framework/uipageview_qt.h>
#include <QtWidgets>

#define BRICK_NONE 32 //' '
#define BRICK_STANDARD 49 //'1'
#define BRICK_CAP_UP 50 //'2'
#define BRICK_CAP_DW 51 //'3'
#define BRICK_CAP_LX 52 //'4'
#define BRICK_CAP_RX 53 //'5'
#define BRICK_THROWABLE 54 //'6'

Brick::Brick(QRectF br_shape)
    : QGraphicsRectItem(br_shape){

    setBrush(QBrush(Qt::darkGreen));
    setPen(QPen(QColor(Qt::black)));
}

void Brick::setIndex(std::pair<int,int> idx){
    _idx = idx;
}

/*
 * Beware that this constructor is not meant to create a fully-functional object
 * It's purpose is mainly unit testing and any other usage is deprecated.
 */
Arena::Arena(double brick_width):
     map_cell_w(brick_width), map_cell_h(brick_width)
{
    memset(bin_map,0,MAP_WIDTH*MAP_HEIGHT);
    memset(map,0,MAP_WIDTH*MAP_HEIGHT);
    timer = new QTimer(this);
}

Arena::Arena(QString fname, double brick_width):
    map_cell_w(brick_width), map_cell_h(brick_width)
{
    memset(bin_map,0,MAP_WIDTH*MAP_HEIGHT);
    memset(map,0,MAP_WIDTH*MAP_HEIGHT);

    QFile map_file(fname);
    if (!map_file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&map_file);
    for (int y=0; y<100 and not in.atEnd(); y++){
        //read all char and discard the newline in the for loop
        QString line = in.readLine();
#ifdef  DEBUG
        assert(line.size()==100);
#endif

        if(line.size()<MAP_WIDTH){
            qDebug("WARNING: line is shorter than expected (%d<%d)/nDumping line: %s",
                   MAP_WIDTH, line.size(), line.toStdString().c_str());
            y--;
            continue;
        }
        line.data();
        for (int x=0; x<100; x++){
            const char b = line.at(x).toLatin1();
            std::pair<int,int> idx(x,y);
            switch(b){
            case BRICK_NONE:
                bin_map[y][x]=none;
                map[y][x]=nullptr;
                break;
            case BRICK_STANDARD:
                bin_map[y][x]=standard;
                map[y][x]=addBrick(idx);
                break;
            case BRICK_CAP_UP:
                bin_map[y][x]=cap_up;
                map[y][x]=addBrick(idx);
                break;
            case BRICK_CAP_DW:
                bin_map[y][x]=cap_dw;
                map[y][x]=addBrick(idx);
                break;
            case BRICK_CAP_LX:
                bin_map[y][x]=cap_lx;
                map[y][x]=addBrick(idx);
                break;
            case BRICK_CAP_RX:
                bin_map[y][x]=cap_rx;
                map[y][x]=addBrick(idx);
                break;
            case BRICK_THROWABLE:
                bin_map[y][x]=throwable;
                map[y][x]=addBrick(idx);
                break;
            }
        }
    }
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(showNextBrick()));
}

void Arena::show(){
    timer->start(1);
}

void Arena::showAll(){
	for(int brick_count = 0; brick_count<MAP_WIDTH*MAP_HEIGHT; brick_count++){
		Brick* b = map[0][brick_count];
		if(b != nullptr) b->show();
	}
}

void Arena::hide()
{
    for(int brick_count = 0; brick_count<MAP_WIDTH*MAP_HEIGHT; brick_count++){
        Brick* b = map[0][brick_count];
        if(b != nullptr) b->hide();
    }

}


void Arena::addToPage(UiPageViewQt* page)
{
    //Brick objects are just view items, as of now,
    //so let's just add them to the page directly.
    for(int brick_count = 0; brick_count<MAP_WIDTH*MAP_HEIGHT; brick_count++){
        Brick* b = map[0][brick_count];
        if(b != nullptr) page->addItem(b);
    }

}

Brick* Arena::addBrick(std::pair<int,int> idx )
{
    Brick* b = new Brick(
                QRectF(
                    idxToPos(idx.first,idx.second),
                    QSizeF(map_cell_w,map_cell_h)
                    )
                );
    b->hide();
    b->setIndex(idx);
    return b;
}


void Arena::showNextBrick(){
	static int brick_count = 0;
    if(brick_count<MAP_WIDTH*MAP_HEIGHT){
        brick_count++;

        Brick* b = map[0][brick_count-1];

        if(b == nullptr)
            showNextBrick();
        else
            b->show();
    }
    else{
        completion_status = true;

        emit build_complete();
        timer->stop();
       //TODO: check if a "disconnect" can be useful here
        brick_count = 0;
    }
}

QPointF Arena::idxToPos(int ix, int iy){
    return QPointF(map_cell_w*ix,map_cell_h*iy);
}

std::pair<int,int> Arena::posToIdx( QPointF pos ){
    int x = pos.x()/map_cell_w;
    int y = pos.y()/map_cell_h;

    return std::pair<int,int>(x,y);
}

Brick* Arena::getBrick(std::pair<int,int> idx ){
    Brick* b = nullptr;
    if((!(idx.first<0) and idx.first<MAP_WIDTH) and
            (!(idx.second<0) and idx.second<MAP_HEIGHT))
        b = map[idx.first][idx.second];
    else
        qDebug("map border reached idx[%d,%d] ", idx.first, idx.second);
    return b;
}

bool Arena::mapComplete(){
    return completion_status;
}
