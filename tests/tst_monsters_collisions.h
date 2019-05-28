#ifndef TST_MONSTERS_COLLISIONS_H
#define TST_MONSTERS_COLLISIONS_H
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>


#include <QtWidgets>
#include "../src/monster.h"
#include "../src/gameworld.h"
#include "../src/arena.h"
#include "../src/behaviors.h"

#include <iostream>
using namespace testing;
using namespace std;

namespace Monster {

class FakeArena: public Arena {
public:

    FakeArena(QGraphicsScene* scene, double brick_width):
        Arena(scene,brick_width)
    {}

    virtual ~FakeArena() override {}

    Brick* getBrick (std::pair<int, int> /*idx*/) override
    {
        Brick* b = nullptr;
        if (next_brick<bricks.size()){
            b = bricks[next_brick];
        }
        next_brick++;
        return b;
    }

    void addBrick(Brick* b)
    {
        bricks.push_back(b);
        return;
    }

    unsigned long getBrickNum(){
        return next_brick;
    }
    void resetBrickNum(){
        next_brick = 0;
        return ;
    }

private:
    unsigned long next_brick = 0;
    std::vector<Brick*> bricks;

};

class DummyMonster: public Monster {
public:
    DummyMonster():
        Monster()
    {
        _checker = new WallsCollisionChecker(&model,30);
        _player_scanner = new PlayerAtSightChecker(&model, 30);
    }

    void setDir(double d){
        model.direction = d;
    }

    pair<double,double> getPos(){
        auto pos = make_pair(model.pos_x,model.pos_y);
        return pos;
    }

    void setPos(pair<double,double> pos){
        model.pos_x = pos.first;
        model.pos_y = pos.second;
        return;
    }

    void checkCollisions(){
        _checker->exec();
    }
private:
    WallsCollisionChecker* _checker;
    PlayerAtSightChecker *_player_scanner;
};

class MonsterCollisions_Test: public testing::Test {
public:

    void SetUp (){
        scene = new QGraphicsScene();
        fa = new FakeArena(scene,8);
        GameWorld::instance().setScene(scene);
    }

    void TearDown(){

        delete fa;
    }

    void testCollision(DummyMonster * monster, double a,
                       std::pair<double, double> pos,
                       std::pair<double, double> exp_pos)
    {
        cout << "*****************************" << endl;
        cout << "testing direction: " << a << endl;
        cout << "*****************************" << endl;

        monster->setDir(a);
        monster->setPos(pos);
        monster->checkCollisions();
        auto new_pos = monster->getPos();
        cout << "monster X delta: (old_x-new_x) " << pos.first << "-" << new_pos.first << "=" << pos.first-new_pos.first << endl;
        cout << "monster Y delta: (old_y-new_y) " << pos.second << "-" << new_pos.second << "=" << pos.second-new_pos.second << endl;
        EXPECT_EQ(new_pos.first, exp_pos.first);
        EXPECT_EQ(new_pos.second, exp_pos.second);

        cout << "requested bricks: " << fa->getBrickNum() << endl;
        fa->resetBrickNum();
    }

    FakeArena* fa;
    QGraphicsScene* scene;
    virtual ~MonsterCollisions_Test(){}

};


TEST_F(MonsterCollisions_Test, four_block_horizontal)
{

    DummyMonster monster;
    std::vector< std::tuple< double, //direction
            std::pair<double, double>, //current position
            std::pair<double, double> > //expected new position
             > test_cases;


    //build a four block wall
    for (int i=0; i<4 ; i++){
        Brick* b = new Brick( QRectF( QPointF(90.0+i*8, 81.0),QSizeF(8.0,8.0) ) );
        cout << "brick: pos=" << b->x() << "," << b->y() << endl;
        cout << "brick bounding rect pos=" << b->boundingRect().x() << "," << b->boundingRect().y()
             << " size=" << b->boundingRect().width() << "," << b->boundingRect().height()
             << endl;
        cout << "brick rect pos=" << b->rect().x() << "," << b->rect().y()
             << " size=" << b->rect().width() << "," << b->rect().height()
             << endl;
        static_cast<FakeArena*>(fa)->addBrick(b);
    }

    //init arena
    try{
        GameWorld::instance().initLevel(fa);
    }
    catch(...){
        cout << "Exception!!! " << endl;
        FAIL();
    }

    //build test vector
    // direction 0 degree
    test_cases.push_back( std::make_tuple(0,make_pair(76,100),make_pair(74.5,100)) );
    // direction 1-89 degrees
    for (double j=1; j<90; j++) {
        test_cases.push_back( std::make_tuple(j,make_pair(76,69.0),make_pair(74.5,65.5)) );
    }
    // direction 90 degree
    test_cases.push_back( std::make_tuple(90,make_pair(76,69.0),make_pair(76,65.5)) );
    // direction 91-189 degrees
    for (double j=91; j<180; j++) {
        test_cases.push_back( std::make_tuple(j,make_pair(135,69.0),make_pair(137.5,65.5)) );
    }
    // direction 180 degree
    test_cases.push_back( std::make_tuple(180,make_pair(135,100),make_pair(137.5,100)) );
    // direction 181-269 degrees
    for (double j=181; j<269; j++) {
        test_cases.push_back( std::make_tuple(j,make_pair(135,100),make_pair(137.5,104.5)) );
    }
    // direction 270 degree
    test_cases.push_back( std::make_tuple(270,make_pair(100,100),make_pair(100,104.5)) );
    // direction 270-359 degrees
    for (double j=271; j<360; j++) {
        test_cases.push_back( std::make_tuple(j,make_pair(76,100),make_pair(74.5,104.5)) );
    }

    for (auto test_case: test_cases){
        testCollision(&monster, std::get<0>(test_case), std::get<1>(test_case),std::get<2>(test_case));
    }

};

TEST_F(MonsterCollisions_Test, four_block_vertical)
{

    DummyMonster monster;
    std::vector< std::tuple< double, //direction
            std::pair<double, double>, //current position
            std::pair<double, double> > //expected new position
             > test_cases;

    //build a four block wall
    for (int i=0; i<4 ; i++){
        Brick* b = new Brick( QRectF( QPointF(70.0, 70.0+i*8),QSizeF(8.0,8.0) ) );
        cout << "brick: pos=" << b->x() << "," << b->y() << endl;
        cout << "brick bounding rect pos=" << b->boundingRect().x() << "," << b->boundingRect().y()
             << " size=" << b->boundingRect().width() << "," << b->boundingRect().height()
             << endl;
        cout << "brick rect pos=" << b->rect().x() << "," << b->rect().y()
             << " size=" << b->rect().width() << "," << b->rect().height()
             << endl;
        static_cast<FakeArena*>(fa)->addBrick(b);
    }

    //build test vector
    // direction 0 degree
    test_cases.push_back( std::make_tuple(0,make_pair(58,58),make_pair(54.5,58)) );
    // direction 1-89 degrees
    for (double j=1; j<90; j++) {
        test_cases.push_back( std::make_tuple(j,make_pair(58,86.0),make_pair(54.5,78.5)) );
    }
    // direction 90 degree
    test_cases.push_back( std::make_tuple(90,make_pair(90,58.0),make_pair(90,54.5)) );
    // direction 91-189 degrees
    for (double j=91; j<180; j++) {
        test_cases.push_back( std::make_tuple(j,make_pair(90,86.0),make_pair(93.5,78.5)) );
    }
    // direction 180 degree
    test_cases.push_back( std::make_tuple(180,make_pair(90,86),make_pair(93.5,86)) );
    // direction 181-269 degrees
    for (double j=181; j<269; j++) {
        test_cases.push_back( std::make_tuple(j,make_pair(90,86),make_pair(93.5,93.5)) );
    }
    // direction 270 degree
    test_cases.push_back( std::make_tuple(270,make_pair(58,113.5),make_pair(58,117.5)) );
    // direction 270-359 degrees
    for (double j=271; j<360; j++) {
        test_cases.push_back( std::make_tuple(j,make_pair(58,86),make_pair(54.5,93.5)) );
    }

    for (auto test_case: test_cases){
        testCollision(&monster, std::get<0>(test_case), std::get<1>(test_case),std::get<2>(test_case));
    }
};


} // namespace Monster
#endif // TST_MONSTERS_COLLISIONS_H
