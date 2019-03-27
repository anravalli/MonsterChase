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

#ifndef PLAYER_H
#define PLAYER_H

#include <QtWidgets>

#define DEF_ENERGY 50
#define MIN_ENERGY 0
#define MAX_ENERGY 100
#define BLINK_DELAY 10

class PlayerSm;

namespace Monster {
class Monster;
}

typedef enum {
    normal,
    rage_available,
    on_rage,
    on_damage,
    dead
} PlayerStates;

typedef enum {
    idle,
    moving
} PlayerSubStates;

enum PlayerDirection {
    player_up,
    player_down,
    player_left,
    player_right
};

typedef struct {
    float energy;
    PlayerStates state;
    PlayerSubStates sub_state;
    int pos_x;
    int pos_y;
    bool direction[4];
    int score;
} PlayerModel;

class PlayerScore;
class PlayerEnergyGauge;
class PlayerShape;
class MonsterChase;

class Player : public QObject
{
    Q_OBJECT

public:
    Player(MonsterChase* w);
    void update();
    ~Player();

    void show();

    void hide();

    void setEnergyGaugePos(int x, int y);

    void setScorePos(int x, int y);

    PlayerEnergyGauge* getEnergyGauge();

    QRectF getIntersectonWith(Monster::Monster *m);

protected:
    bool eventFilter(QObject *watched, QEvent *event) Q_DECL_OVERRIDE;

private:
    MonsterChase* world;
    PlayerModel model = {
        DEF_ENERGY, //energy
        normal, //state
        idle, //sub_state
        100, //pos_x
        100, //pos_y
        {false,false,false,false}, //direction
        0 // score
    };
    PlayerShape* shape;
    PlayerEnergyGauge* energy_gauge;
    PlayerScore* score;
    //bool direction[4]={false,false,false,false};
    PlayerSm* pstates[5]={nullptr,nullptr,nullptr,nullptr,nullptr};

    void move();
    bool handleKey(int key, bool released);

    void computeState();
    void checkCollisionsWithMonsters();
    void updateViews();
};

#endif // PLAYER_H
