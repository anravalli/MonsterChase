#ifndef ARENA_H
#define ARENA_H

#include <QGraphicsItem>
#include <QFile>
#include <QTextStream>

#define MAP_WIDTH 100
#define MAP_HEIGHT 100

typedef enum {
    none,
    standard,
    cap_up,
    cap_dw,
    cap_lx,
    cap_rx,
    throwable
} BrickType;

class Brick: public QGraphicsRectItem
{
public:
    Brick(QRectF br_shape);

    void setIndex(std::pair<int,int> idx);
private:
    std::pair<int,int> _idx;
};

class Arena: public QObject
{
    Q_OBJECT

signals:
    void build_complete();

public:
    Arena(QString fname, QGraphicsScene *scene);

    bool mapComplete();
    void startShowMap();

public slots:
    void showNextBrick();

private:
    char bin_map[MAP_HEIGHT][MAP_WIDTH];
    Brick* map[MAP_HEIGHT][MAP_WIDTH];

    int brick_count = 0;
    bool completion_status = false;
    QTimer* timer;

    QGraphicsScene *_scene;

    QPointF idxToPos(int ix, int iy){
        return QPoint(map_cell_w*ix,map_cell_h*iy);
    }

    float map_cell_w;
    float map_cell_h;
    Brick* addBrick(QGraphicsScene *s, std::pair<int,int> idx );

};

#endif // ARENA_H

