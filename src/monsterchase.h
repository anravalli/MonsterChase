/*
 *	Monster Chase: a testing playground for behaviors trees
 *
 *	Copyright 2019 Andrea Ravalli <anravalli @ gmail.com>
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

#ifndef MONSTERCHASE_H
#define MONSTERCHASE_H

#include "gameviews.h"

class MonsterChase : public QObject
{
    Q_OBJECT

public:
    explicit MonsterChase();


    ~MonsterChase() override;

    void show();

public slots:
    void gameStep() ;
    void pause();
    void start();

protected:

private:
    QGraphicsView* view;
    QGraphicsScene* scene;
    QTimer* timer;
    PlayTime* ptime;

    void setUpView();
    void addPlayTime();

};

#endif // MONSTERCHASE_H
