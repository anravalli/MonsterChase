#include "gameworld.h"

#include "player.h"
#include "monster.h"
#include "arena.h"
#include "gameconfig.h"

GameWorld::GameWorld()
{

}


GameWorld::~GameWorld(){}

GameWorld& GameWorld::instance(){
    static GameWorld instance;
    return instance;
}

void GameWorld::start()
{
    player->show();
    for (auto m: monsters)
        m->show();
}

void GameWorld::nextFrame() {
    player->update();
    for (auto m: monsters)
        m->update();
}

void GameWorld::initLevel(Arena* a)
{
    arena = a;
    addPlayer();
    addMonsters();
    arena->startShowMap();
}

void GameWorld::addPlayer(){
    player = new Player();
    player->setEnergyGaugePos(
                GameConfig::playground_width/2,
                GameConfig::playground_height+GameConfig::playground_border_height*0.3);
    player->setScorePos(
                GameConfig::playground_width-35,
                -GameConfig::playground_border_height*0.6);
    player->hide();
}

void GameWorld::addMonsters(){
    //Adding Blinky at x=200 y=200
    Monster::Monster* m = Monster::monsterFactory(
                Monster::MonsterType::Blinky,
                QPointF(200,200));
    m->hide();
    monsters.push_back(m);

    //Adding Pinky at x=600 y=200
    m = Monster::monsterFactory(
                Monster::MonsterType::Pinky,
                QPointF(600,200));
    m->hide();
    monsters.push_back(m);
}

void GameWorld::setScene(QGraphicsScene *s){
    scene = s;
    return;
}

std::vector<Monster::Monster*> GameWorld::getMonsters(){
    return monsters;
}

std::vector<Brick*> GameWorld::getWallsAround(QPointF tl, QPointF br){
    std::pair<int,int> tl_idx = arena->posToIdx(tl);
    std::pair<int,int> br_idx = arena->posToIdx(br);
    std::pair<int,int> idx;
    std::vector<Brick*> wall;
    for(int x=tl_idx.first-1; x<br_idx.first+1; x++){
        for (int y=tl_idx.second-1; y<br_idx.second+1; y++){
            //TODO
            idx.first = y;
            idx.second = x;
            Brick* b = arena->getBrick(idx);
            if (!(b==nullptr))
                wall.push_back(b);
        }
    }
    return wall;
}

Player* GameWorld::getPlayer(){
    return player;
}

void GameWorld::addToScene(QGraphicsItem *item){
    scene->addItem(item);
    return;
}



