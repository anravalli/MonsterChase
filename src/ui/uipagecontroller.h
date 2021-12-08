#ifndef GAMEPAGE_H
#define GAMEPAGE_H

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

#include <QObject>

class UiPageQt;

class UiPageController: public QObject
{
    Q_OBJECT
public:
    explicit UiPageController(UiPageController *parent = nullptr);

    //show the page
    virtual void show() = 0;
    virtual void exit() = 0;

    UiPageQt *getPage() const;

protected:
    bool eventFilter(QObject *watched, QEvent *event) Q_DECL_OVERRIDE;
    virtual bool handleKey(int key, bool released) = 0;

    UiPageQt *page;

private:

    //virtual bool handlePointDev(int key, bool released);
};

#endif // GAMEPAGE_H
