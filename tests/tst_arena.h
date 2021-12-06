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
        arena = new Arena ("../../MonsterChase/resources/map.txt", 8);
    }
    Arena* arena = 0;
    QGraphicsScene* scene = 0;
};

TEST_F(Arena_Test, get_brick_0){
    std::pair<int,int> p(0,0);
    Brick* b = arena->getBrick(p);
    //The assertion below should evaluate as: b = (b ? b : nullptr);
    EXPECT_NE(static_cast<Brick*>(nullptr), b);
}

TEST_F(Arena_Test, get_out_of_map_bricks){

    vector< pair<int,int> > input_vector;

    input_vector.push_back(make_pair(-1,100));
    input_vector.push_back(make_pair(1,100));
    input_vector.push_back(make_pair(0,100));
    input_vector.push_back(make_pair(99,100));
    input_vector.push_back(make_pair(-1,102));
    input_vector.push_back(make_pair(-1,99));
    input_vector.push_back(make_pair(-1,0));
    input_vector.push_back(make_pair(100,10));
    input_vector.push_back(make_pair(101,1));
    for (auto i: input_vector){
        cout << "get brick " << i.first << ", " << i.second << endl;
        Brick* b = arena->getBrick(i);
        EXPECT_EQ(static_cast<Brick*>(nullptr), b);
    }
}

#endif // TST_ARENA_H
