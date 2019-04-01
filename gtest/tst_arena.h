#ifndef TST_ARENA_H
#define TST_ARENA_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include <iostream>

#include "arena.h"

using namespace testing;
using namespace std;

class Arena_Test: public testing::Test {
    //Q_OBJECT
public:
    void SetUp(){
        //QObject * o = new QObject();

        scene = new QGraphicsScene();
        arena = new Arena ("../../MonsterChase/resources/map.txt", scene);
    }
    Arena* arena = 0;
    QGraphicsScene* scene = 0;
};

TEST_F(Arena_Test, get_brick_0){
    //std::cout << "checking 0, 0\n";
    std::pair<int,int> p(0,0);
    Brick* b = arena->getBrick(p);
    //b = (b ? b : nullptr);
    ASSERT_NE((Brick*)nullptr, b);
}

#endif // TST_ARENA_H
