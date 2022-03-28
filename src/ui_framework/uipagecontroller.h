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

class UiPageViewQt;

class UiPageController: public QObject
{
    Q_OBJECT
public:
    explicit UiPageController(UiPageController *parent = nullptr);

    //show the page
    virtual void show();
    virtual void exit();

    UiPageViewQt *getPageView() const;

protected:
    bool eventFilter(QObject *watched, QEvent *event) Q_DECL_OVERRIDE;
    virtual bool handleKey(int key, bool released) = 0;

    template<class T> void initPageView();

    UiPageViewQt *page_view;
    UiPageController *parent_page;

private:

};

template<class T> void UiPageController::initPageView()
{
    UiPageViewQt *view = nullptr;
    if(parent_page)
        view = parent_page->getPageView();
    page_view = new T(view);
}


#endif // GAMEPAGE_H
