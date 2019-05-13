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
    PlayTime();

    void increase();

private:
    QColor color;
    int time=0;
    int frame_counter=25;
};

#endif // GAMEVIEWS_H
