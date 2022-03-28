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


#include "uiviewitems_qt.h"
#include "gameconfig.h"
#include <QOpenGLWidget>

#define USE_OGL 0
//#define DEBUG

UiBaseQGraphicsView::UiBaseQGraphicsView(QGraphicsScene *scene) : QGraphicsView(scene)
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
#if USE_OGL
    QOpenGLWidget *gl = new QOpenGLWidget();
    QSurfaceFormat format;
    format.setSamples(4);
    QPair<int, int> gl_version = format.version();
    gl->setFormat(format);
    this->setViewport(gl);
    qDebug("Opengl Version: %d.%d", gl_version.first, gl_version.second);
    if(gl->context()){
        qDebug () << (const char*)gl->context()->functions()->glGetString(GL_VERSION);
        qDebug () << (const char*)gl->context()->functions()->glGetString(GL_EXTENSIONS);
    }
#endif
}

const QRect *UiBaseQGraphicsView::innerBorder(){
    return inner_border;
}

void UiBaseQGraphicsView::keyPressEvent(QKeyEvent *event){
#ifdef  DEBUG
    qDebug("Event received by GameView %d (%s)",event->key(), event->text().toStdString().c_str());
#endif
    QGraphicsView::keyPressEvent(event);
    return;
}

void UiBaseQGraphicsView::resizeEvent(QResizeEvent *)
{
}

