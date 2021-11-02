#include "gameviews.h"
#include "gameconfig.h"


GameView::GameView(QGraphicsScene *scene) : QGraphicsView(scene)
{
    setFocusPolicy(Qt::StrongFocus);
    setDragMode(NoDrag);
    setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    setFixedSize(QSize(
                     GameConfig::playground_view_width,
                     GameConfig::playground_view_height));
    inner_border = new QRect(GameConfig::playground_border_width,
                             GameConfig::playground_border_height,
                             GameConfig::playground_width-GameConfig::playground_border_width,
                             GameConfig::playground_height-GameConfig::playground_border_height);
}

const QRect *GameView::innerBorder(){
    return inner_border;
}

void GameView::keyPressEvent(QKeyEvent *event){
#ifdef  DEBUG
    qDebug("Event received by GameView %d (%s)",event->key(), event->text().toStdString().c_str());
#endif
    QGraphicsView::keyPressEvent(event);
    return;
}

void GameView::resizeEvent(QResizeEvent *)
{
}


PlayTime::PlayTime(const unsigned short framerate)
    :color(255,127,127), frame_max(framerate), frame_counter(framerate)
{
    QFont font("Helvetica",14,QFont::Bold);
    this->setFont(font);
    this->setPen(QPen(color));
}

void PlayTime::increase(){
    if(!frame_counter){
        frame_counter=frame_max;
        time++;
    }
    else
        frame_counter--;
    this->setText(QString::asprintf("%04d", time));
    return;
}
