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
#include <QtWidgets>
#include <QObject>
#include "uipagecontroller.h"
#include "uipageview_qt.h"


UiPageController::UiPageController(UiPageController *parent):
    QObject((QObject *)parent), parent_page(parent)
{
}

bool UiPageController::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
#ifdef  DEBUG
        qDebug("%d KeyPress received by Player", __LINE__);
#endif
        QKeyEvent* ke = static_cast<QKeyEvent*>(event);
        int key = ke->key();
        return handleKey(key, false);
    } else  if (event->type() == QEvent::KeyRelease) {
        QKeyEvent* ke = static_cast<QKeyEvent*>(event);
        int key = ke->key();
        return handleKey(key, true);
    }
    // Make sure the rest of events are handled
    return QObject::eventFilter(watched, event);
}

UiPageViewQt *UiPageController::getPageView() const
{
    return page_view;
}

void UiPageController::show()
{
    QApplication::instance()->installEventFilter(this);
    page_view->show();
}

void UiPageController::exit(){
    qDebug("UiPageController::exit()");
    if(parent_page)
    {
        page_view->hide();
        QApplication::instance()->removeEventFilter(this);
        parent_page->show();
    }
}
