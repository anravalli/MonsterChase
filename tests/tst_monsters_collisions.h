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

    virtual ~FakeArena() override {}

    Brick* getBrick (std::pair<int, int> /*idx*/)
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
};

class MonsterCollisions_Test: public testing::Test {
public:

    void SetUp (){
        fa = new FakeArena();

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

    virtual ~MonsterCollisions_Test(){}

};


TEST_F(MonsterCollisions_Test, four_block_horizontal)
{

    DummyMonster monster;
    std::vector< std::tuple< double,
            std::pair<double, double>,
            std::pair<double, double> > > test_cases;


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
    try{
        GameWorld::instance().initLevel(fa);
    }
    catch(...){
        cout << "*****************************" << endl;
        cout << "Exception!!! " << endl;
        cout << "*****************************" << endl;
    }
    //build a direction vector ranging between 0 and 180 degrees
    // 0
    test_cases.push_back( std::make_tuple(0,make_pair(76,100),make_pair(74.5,100)) );

    for (double j=1; j<90; j++) {
        test_cases.push_back( std::make_tuple(j,make_pair(76,69.0),make_pair(74.5,65.5)) );
    }

    cout << "*****************************" << endl;
    cout << "direction range 90-179" << endl;
    cout << "*****************************" << endl;
    cout << "direction=" <<90 << endl;
    monster.setDir(90);
    monster.setPos(make_pair(76,69.0));
    monster.checkCollisions();
    auto new_pos = monster.getPos();
    cout << "monster X delta: (old_x-new_x) 76-" << new_pos.first << "=" << 76-new_pos.first << endl;
    cout << "monster Y delta: (old_y-new_y) 69-" << new_pos.second << "=" << 69-new_pos.second << endl;
    EXPECT_EQ(new_pos.first, 76);
    EXPECT_EQ(new_pos.second, 65.5);

    for (double j=91; j<180; j++) {
        cout << "*****************************" << endl;
        cout << "direction=" << j << endl;
        monster.setDir(j);
        monster.setPos(make_pair(135,69.0));
        monster.checkCollisions();
        auto new_pos = monster.getPos();
        cout << "monster X delta: (old_x-new_x) 135-" << new_pos.first << "=" << 135-new_pos.first << endl;
        cout << "monster Y delta: (old_y-new_y) 69-" << new_pos.second << "=" << 69-new_pos.second << endl;
        EXPECT_EQ(new_pos.first, 137.5);
        EXPECT_EQ(new_pos.second, 65.5);
    }

    cout << "*****************************" << endl;
    cout << "direction range 180-269" << endl;
    cout << "*****************************" << endl;
    cout << "direction=" << 180 << endl;
    monster.setDir(180);
    monster.setPos(make_pair(135,100));
    monster.checkCollisions();
    new_pos = monster.getPos();
    cout << "monster X delta: (old_x-new_x) 135-" << new_pos.first << "=" << 135-new_pos.first << endl;
    cout << "monster Y delta: (old_y-new_y) 100-" << new_pos.second << "=" << 100-new_pos.second << endl;
    EXPECT_EQ(new_pos.first, 137.5);
    EXPECT_EQ(new_pos.second, 100);


    for (double j=181; j<270; j++) {
        cout << "*****************************" << endl;
        cout << "direction=" << j << endl;
        monster.setDir(j);
        monster.setPos(make_pair(135,100));
        monster.checkCollisions();
        auto new_pos = monster.getPos();
        cout << "monster X delta: (old_x-new_x) 135-" << new_pos.first << "=" << 135-new_pos.first << endl;
        cout << "monster Y delta: (old_y-new_y) 100-" << new_pos.second << "=" << 100-new_pos.second << endl;
        EXPECT_EQ(new_pos.first, 137.5);
        EXPECT_EQ(new_pos.second, 104.5);
    }

    cout << "*****************************" << endl;
    cout << "direction range 270-359" << endl;
    cout << "*****************************" << endl;
    cout << "direction=" << 270 << endl;
    monster.setDir(270);
    monster.setPos(make_pair(100,100));
    monster.checkCollisions();
    new_pos = monster.getPos();
    cout << "monster X delta: (old_x-new_x) 100-" << new_pos.first << "=" << 100-new_pos.first << endl;
    cout << "monster Y delta: (old_y-new_y) 100-" << new_pos.second << "=" << 100-new_pos.second << endl;
    EXPECT_EQ(new_pos.first, 100);
    EXPECT_EQ(new_pos.second, 104.5);

    for (double j=271; j<360; j++) {
        cout << "*****************************" << endl;
        cout << "direction=" << j << endl;
        monster.setDir(j);
        monster.setPos(make_pair(76,100));
        monster.checkCollisions();
        auto new_pos = monster.getPos();
        cout << "monster X delta: (old_x-new_x) 100-" << new_pos.first << "=" << 100-new_pos.first << endl;
        cout << "monster Y delta: (old_y-new_y) 100-" << new_pos.second << "=" << 100-new_pos.second << endl;
        EXPECT_EQ(new_pos.first, 74.5);
        EXPECT_EQ(new_pos.second, 104.5);
    }
};

TEST_F(MonsterCollisions_Test, four_block_vertical)
{

    DummyMonster monster;

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

    //build a direction vector ranging between 0 and 180 degrees

    cout << "*****************************" << endl;
    cout << "direction range  0-89" << endl;
    cout << "*****************************" << endl;
    cout << "direction=" << 0 << endl;
    monster.setDir(0);
    monster.setPos(make_pair(58,58));
    monster.checkCollisions();
    auto new_pos = monster.getPos();
    cout << "monster X delta: (old_x-new_x) 58-" << new_pos.first << "=" << 58-new_pos.first << endl;
    cout << "monster Y delta: (old_y-new_y) 58-" << new_pos.second << "=" << 58-new_pos.second << endl;
    EXPECT_EQ(new_pos.first, 54.5);
    EXPECT_EQ(new_pos.second, 58);

    for (double j=1; j<90; j++) {
        cout << "*****************************" << endl;
        cout << "direction=" << j << endl;
        monster.setDir(j);
        monster.setPos(make_pair(58,86));
        monster.checkCollisions();
        auto new_pos = monster.getPos();
        cout << "monster X delta: (old_x-new_x) 58-" << new_pos.first << "=" << 58-new_pos.first << endl;
        cout << "monster Y delta: (old_y-new_y) 86-" << new_pos.second << "=" << 86-new_pos.second << endl;
        EXPECT_EQ(new_pos.first, 54.5);
        EXPECT_EQ(new_pos.second, 78.5);
    }

    cout << "*****************************" << endl;
    cout << "direction range 90-179" << endl;
    cout << "*****************************" << endl;
    cout << "direction=" <<90 << endl;
    monster.setDir(90);
    monster.setPos(make_pair(90.0,58.0));
    monster.checkCollisions();
    new_pos = monster.getPos();
    cout << "monster X delta: (old_x-new_x) 90-" << new_pos.first << "=" << 90-new_pos.first << endl;
    cout << "monster Y delta: (old_y-new_y) 58-" << new_pos.second << "=" << 58-new_pos.second << endl;
    EXPECT_EQ(new_pos.first, 90.0);
    EXPECT_EQ(new_pos.second, 54.5);

    for (double j=91; j<180; j++) {
        cout << "*****************************" << endl;
        cout << "direction=" << j << endl;
        monster.setDir(j);
        monster.setPos(make_pair(90,86));
        monster.checkCollisions();
        auto new_pos = monster.getPos();
        cout << "monster X delta: (old_x-new_x) 90-" << new_pos.first << "=" << 90-new_pos.first << endl;
        cout << "monster Y delta: (old_y-new_y) 86-" << new_pos.second << "=" << 86-new_pos.second << endl;
        EXPECT_EQ(new_pos.first, 93.5);
        EXPECT_EQ(new_pos.second, 78.5);
    }

    cout << "*****************************" << endl;
    cout << "direction range 180-269" << endl;
    cout << "*****************************" << endl;
    cout << "direction=" << 180 << endl;
    monster.setDir(180);
    monster.setPos(make_pair(90,86));
    monster.checkCollisions();
    new_pos = monster.getPos();
    cout << "monster X delta: (old_x-new_x) 135-" << new_pos.first << "=" << 90-new_pos.first << endl;
    cout << "monster Y delta: (old_y-new_y) 86-" << new_pos.second << "=" << 86-new_pos.second << endl;
    EXPECT_EQ(new_pos.first, 93.5);
    EXPECT_EQ(new_pos.second, 86);

    for (double j=181; j<270; j++) {
        cout << "*****************************" << endl;
        cout << "direction=" << j << endl;
        monster.setDir(j);
        monster.setPos(make_pair(90,86));
        monster.checkCollisions();
        auto new_pos = monster.getPos();
        cout << "monster X delta: (old_x-new_x) 90-" << new_pos.first << "=" << 90-new_pos.first << endl;
        cout << "monster Y delta: (old_y-new_y) 86-" << new_pos.second << "=" << 86-new_pos.second << endl;
        EXPECT_EQ(new_pos.first, 93.5);
        EXPECT_EQ(new_pos.second, 93.5);
    }

    cout << "*****************************" << endl;
    cout << "direction range 270-359" << endl;
    cout << "*****************************" << endl;
    cout << "direction=" << 270 << endl;
    monster.setDir(270);
    monster.setPos(make_pair(58,113.5));
    monster.checkCollisions();
    new_pos = monster.getPos();
    cout << "monster X delta: (old_x-new_x) 58-" << new_pos.first << "=" << 58-new_pos.first << endl;
    cout << "monster Y delta: (old_y-new_y) 113.5-" << new_pos.second << "=" << 113.5-new_pos.second << endl;
    EXPECT_EQ(new_pos.first, 58);
    EXPECT_EQ(new_pos.second, 117.5);

    for (double j=271; j<360; j++) {
        cout << "*****************************" << endl;
        cout << "direction=" << j << endl;
        monster.setDir(j);
        monster.setPos(make_pair(58,86));
        monster.checkCollisions();
        auto new_pos = monster.getPos();
        cout << "monster X delta: (old_x-new_x) 58-" << new_pos.first << "=" << 58-new_pos.first << endl;
        cout << "monster Y delta: (old_y-new_y) 86-" << new_pos.second << "=" << 86-new_pos.second << endl;
        EXPECT_EQ(new_pos.first, 54.5);
        EXPECT_EQ(new_pos.second, 93.5);
    }
};


} // namespace Monster
#endif // TST_MONSTERS_COLLISIONS_H
