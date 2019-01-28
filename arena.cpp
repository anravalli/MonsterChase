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
    //_idx = idx;

    //shape = new QGraphicsRectItem(br_shape);
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
    if (map_file.canReadLine())
        qDebug("File can be read");
    if (map_file.isOpen())
        qDebug("File is open");
    if (map_file.exists())
        qDebug("File exist");
    if (map_file.size())
        qDebug("File size is %d", map_file.size());
    //QByteArray()
    QTextStream in(&map_file);
    //QString str = in.readAll();
    //qDebug("File size %d", str.size());
    //qDebug("File content %s", str);
    for (int i=0; i<100 and not in.atEnd(); i++){
        QString line = in.readLine(100);
        //assert(line.size()==100);
        if(line.size()<100)
            continue;
        line.data();
        for (int j=0; j<100; j++){
            const char b = line.at(j).toLatin1();
            std::pair<int,int> idx(i,j);
            switch(b){
            case BRICK_NONE:
                bin_map[i][j]=none;
                map[i][j]=nullptr;
                break;
            case BRICK_STANDARD:
                bin_map[i][j]=standard;
                map[i][j]=addBrick(scene, idx);
                break;
            case BRICK_CAP_UP:
                bin_map[i][j]=cap_up;
                map[i][j]=addBrick(scene, idx);
                break;
            case BRICK_CAP_DW:
                bin_map[i][j]=cap_dw;
                map[i][j]=addBrick(scene, idx);
                break;
            case BRICK_CAP_LX:
                bin_map[i][j]=cap_lx;
                map[i][j]=addBrick(scene, idx);
                break;
            case BRICK_CAP_RX:
                bin_map[i][j]=cap_rx;
                map[i][j]=addBrick(scene, idx);
                break;
            case BRICK_THROWABLE:
                bin_map[i][j]=throwable;
                map[i][j]=addBrick(scene, idx);
                break;
            }
        }
    }
}

void Arena::buildMap(){
    if(not mapComplete()){
        //addBrick();
    }
}

//void Arena::addBrick(){
//    if(brick_count<100*100)
//        brick_count++;
//    else
//        completion_status = true;
//}

Brick* Arena::addBrick(QGraphicsScene *s, std::pair<int,int> idx ){
    Brick* b = new Brick( QRectF( idxToPos(idx.first,idx.second),QSizeF(map_cell_w,map_cell_h) ) );
    //b->hide();
    s->addItem(b);
    return b;
}

void Arena::showBrick(std::pair<int,int> idx){
    map[idx.first][idx.second]->show();
}

bool Arena::mapComplete(){
    return completion_status;
}
