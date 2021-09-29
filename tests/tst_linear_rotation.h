#ifndef TST_LINEAR_ROTATION_H
#define TST_LINEAR_ROTATION_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>


#include <QtWidgets>
#include "../src/behaviors.h"

#include <iostream>
#include <vector>

using namespace testing;
using namespace std;

class LinearRotation_Tests: public testing::Test {
public:
    void SetUp(){
        rotate = new LinearRotation(&model,5);
    }
protected:
    LinearRotation* rotate = nullptr;
    Monster::MonsterModel model = {
        0,
        Monster::MonsterType::Clyde,
        Monster::MonsterStates::patrol,
        Monster::MonsterSubStates::move,
        0, //pos_x
        0, //pos_y
        0, //prevpos_x
        0, //prev_pos_y
        0, //direction
        0, //target_x
        0, //target_y
        0, //target direction
        0  //curent_speed
    };

};

TEST_F(LinearRotation_Tests, ccw_or_cw){
    //destination, target, expected
    vector<tuple<int,int,int>> tests;
    tests.push_back( make_tuple(30,300,25) );
    tests.push_back( make_tuple(300,30,305) );
    tests.push_back( make_tuple(60,30,55) );
    tests.push_back( make_tuple(30,60,35) );
    tests.push_back( make_tuple(300,200,295) );
    tests.push_back( make_tuple(200,300,205) );
    for (auto test: tests){
        cout << "Testing: dir=" << get<0>(test) << ", target_dir=" << get<1>(test) << ", expected_dir=" << get<2>(test) << endl;
        model.direction = get<0>(test);
        model.target_direction = get<1>(test);
        rotate->exec();
        EXPECT_EQ(model.direction, get<2>(test));
    }

}

TEST_F(LinearRotation_Tests, corners){
    //destination, target, expected
    vector<tuple<int,int,int>> tests;
/*
 *  test cases not admited: 0,360,0; 360,0,360;
*/
    tests.push_back( make_tuple(0,0,0) );
    tests.push_back( make_tuple(90,90,90) );
    tests.push_back( make_tuple(90,180,95) );
    tests.push_back( make_tuple(180,90,175) );
    tests.push_back( make_tuple(180,270,185) );
    tests.push_back( make_tuple(0,180,5) );
    tests.push_back( make_tuple(360,180,355) );
    tests.push_back( make_tuple(180,360,185) );
    tests.push_back( make_tuple(180,0,175) );
    tests.push_back( make_tuple(0,270,355) );
    tests.push_back( make_tuple(360,270,355) );
    for (auto test: tests){
        cout << "Testing: dir=" << get<0>(test) << ", target_dir=" << get<1>(test) << ", expected_dir=" << get<2>(test) << endl;
        model.direction = get<0>(test);
        model.target_direction = get<1>(test);
        int expected = get<2>(test);
        rotate->exec();
        EXPECT_EQ(model.direction, expected);
    }

}
#endif // TST_LINEAR_ROTATION_H
