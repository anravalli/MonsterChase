#ifndef GAME_H
#define GAME_H

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


#include "ui/uipage_controller.h"

class UiPageQt;
class QTimer;
class PlayTime;

class GameController : public UiPageController
{
    Q_OBJECT
public:
    explicit GameController(UiPageController *parent = nullptr);
    ~GameController() override;
    void show() override;
    void exit() override;

public slots:
    void gameStep() ;
    void start();

protected:
    bool handleKey(int key, bool released) override;

private:
    QTimer* timer;
    PlayTime* ptime;

    bool is_paused; //temporary: this "state variable" has to be changed to a "real" state

    void setUpView();
    void addPlayTime();

signals:

};

#endif // GAME_H
