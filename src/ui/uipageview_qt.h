#ifndef UIPAGEVIEW_H
#define UIPAGEVIEW_H

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

class UiBaseQtView;

class UiPageQt: QObject
{
    Q_OBJECT
public:
    explicit UiPageQt(UiPageQt *parent = nullptr);

    void SetPageColor(QColor color);

    double width();
    double height();
    void addItem(QGraphicsItem *item);
    void show();
    void hide();

    virtual ~UiPageQt();

    UiBaseQtView *getView() const;

private:
    UiBaseQtView *view;
    QGraphicsScene *scene;

public slots:

signals:

};

#endif // UIPAGEVIEW_H
