#ifndef GAMEVIEWS_H
#define GAMEVIEWS_H

#include <QtWidgets>

class GameView : public QGraphicsView
{
public:
    GameView(QGraphicsScene *scene);

    QRect const * innerBorder();

protected:
    virtual void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;

    virtual void resizeEvent(QResizeEvent *) Q_DECL_OVERRIDE;

private:
    QRect* inner_border;

};

class PlayTime : public QGraphicsSimpleTextItem
{
public:
    PlayTime(unsigned short framerate);

    void increase();

private:
    QColor color;
    int time=0;
    unsigned short frame_max;
    int frame_counter;
};

#endif // GAMEVIEWS_H
