#ifndef UIBASEQTVIEW_H
#define UIBASEQTVIEW_H

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

class UiBaseQGraphicsView: public QGraphicsView
{
public:
    UiBaseQGraphicsView(QGraphicsScene *scene);

    QRect const * innerBorder();

protected:
    virtual void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;

    virtual void resizeEvent(QResizeEvent *) Q_DECL_OVERRIDE;

private:
    QRect* inner_border;

};

#endif // UIBASEQTVIEW_H
