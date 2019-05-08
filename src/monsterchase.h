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

#include <QtWidgets>

class Arena;
class Brick;
class Player;
class PlayTime;
namespace Monster {
class Monster;
}

class GameWorld {
public:
    virtual std::vector<Monster::Monster*> getMonsters() = 0;
    virtual std::vector<Brick*> getWallsAround(QPointF tl, QPointF br) = 0;
    virtual Player* getPlayer() = 0;
    virtual QGraphicsScene* getScene() = 0;

    virtual ~GameWorld();
};

class MonsterChase : public QObject, public GameWorld
{
    Q_OBJECT
    friend class Player;
    friend class Monster::Monster;

public:
    static MonsterChase& instance();

    //avoid copy
    MonsterChase(MonsterChase const&) = delete;
    void operator=(MonsterChase const&)  = delete;

    ~MonsterChase() override;

    void show();

public slots:
    void gameStep() ;
    void pause();
    void start();

protected:
    std::vector<Monster::Monster*> getMonsters() override;
    std::vector<Brick*> getWallsAround(QPointF tl, QPointF br) override;
    Player* getPlayer() override;
    QGraphicsScene* getScene() override;

private:
    explicit MonsterChase();
    QGraphicsView* view;
    QGraphicsScene* scene;
    QTimer* timer;

    Arena* arena;
    PlayTime* ptime;

    Player* player;

    std::vector<Monster::Monster*> monsters;

    void setUpView();
    void addPlayTime();
    void addPlayer();
    void addMonsters();
    void buildArena();

};

#endif // MONSTERCHASE_H
