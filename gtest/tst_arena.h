#ifndef TST_ARENA_H
#define TST_ARENA_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include <iostream>

#include "arena.h"

using namespace testing;
using namespace std;

class Arena_Test: public testing::Test {
public:
    void SetUp(){
        scene = new QGraphicsScene();
        arena = new Arena ("../../MonsterChase/resources/map.txt", scene);
    }
    Arena* arena = 0;
    QGraphicsScene* scene = 0;
};

TEST_F(Arena_Test, get_brick_0){
    std::pair<int,int> p(0,0);
    Brick* b = arena->getBrick(p);
    //The assertion below should evaluate as: b = (b ? b : nullptr);
    ASSERT_NE((Brick*)nullptr, b);
}

#endif // TST_ARENA_H
