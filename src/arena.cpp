#include "arena.h"
#include <assert.h>
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


Arena::Arena(QString fname, QGraphicsScene *scene){
    memset(bin_map,0,100*100);
    memset(map,0,100*100);

    map_cell_w = scene->sceneRect().width()/MAP_WIDTH;
    map_cell_h = scene->sceneRect().height()/MAP_HEIGHT;

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
                map[y][x]=addBrick(scene, idx);
                break;
            case BRICK_CAP_UP:
                bin_map[y][x]=cap_up;
                map[y][x]=addBrick(scene, idx);
                break;
            case BRICK_CAP_DW:
                bin_map[y][x]=cap_dw;
                map[y][x]=addBrick(scene, idx);
                break;
            case BRICK_CAP_LX:
                bin_map[y][x]=cap_lx;
                map[y][x]=addBrick(scene, idx);
                break;
            case BRICK_CAP_RX:
                bin_map[y][x]=cap_rx;
                map[y][x]=addBrick(scene, idx);
                break;
            case BRICK_THROWABLE:
                bin_map[y][x]=throwable;
                map[y][x]=addBrick(scene, idx);
                break;
            }
        }
    }
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(showNextBrick()));
}

void Arena::startShowMap(){
    timer->start(10);
}


Brick* Arena::addBrick(QGraphicsScene *s, std::pair<int,int> idx ){
    Brick* b = new Brick( QRectF( idxToPos(idx.first,idx.second),QSizeF(map_cell_w,map_cell_h) ) );
    b->hide();
    b->setIndex(idx);
    s->addItem(b);
    return b;
}

void Arena::showNextBrick(){
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
       //check if disconnect can be useful here
    }
}

QPointF Arena::idxToPos(int ix, int iy){
    return QPoint(map_cell_w*ix,map_cell_h*iy);
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
