#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include "QGraphicsScene"

class Arena;
class Brick;
class Player;
namespace Monster {
class Monster;
}

class GameWorld: public QObject
{
    Q_OBJECT

public:
    static GameWorld& instance();


    void nextFrame();

    void initLevel(Arena *a);

    virtual std::vector<Monster::Monster*> getMonsters();
    virtual std::vector<Brick*> getWallsAround(QPointF tl, QPointF br);
    virtual Player* getPlayer();
    //virtual QGraphicsScene* getScene();
    void addToScene(QGraphicsItem* item);

    void addPlayer();
    void addMonsters();
    void buildArena();

    //avoid copy
    GameWorld(GameWorld const&) = delete;
    void operator=(GameWorld const&)  = delete;

    //TODO: this part has to be refactored introducing ViewFacade
    void setScene(QGraphicsScene* s);

    virtual ~GameWorld();

public slots:
    void start();

private:
    GameWorld();

    Arena* arena;
    Player* player;
    std::vector<Monster::Monster*> monsters;

    QGraphicsScene* scene;

};


#endif // GAMEWORLD_H
