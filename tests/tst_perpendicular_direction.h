#ifndef TST_PERPENDICULAR_DIRECTION_H
#define TST_PERPENDICULAR_DIRECTION_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>


#include <QtWidgets>
#include "../src/behaviors.h"

#include <iostream>
#include <vector>

using namespace testing;
using namespace std;

class PerpendicularDirection_Tests: public testing::Test {
public:
    void SetUp(){
        select = new PerpendicularDirection(&model);
    }
protected:
    PerpendicularDirection* select = nullptr;
    Monster::MonsterModel model = {
        0,
        Monster::MonsterType::Clyde,
        Monster::MonsterStates::patrol,
        Monster::MonsterSubStates::move,
        0.0,
        0.0,
        0.0,
        0.0,
        0.0,
        0.0
    };

    //void check

};

TEST_F(PerpendicularDirection_Tests, regular_directions){
    //current_dir, expected_ccw, expected_cw
    vector<tuple<double,double, double>> tests;
    tests.push_back( make_tuple(0, 90, 270) );
    tests.push_back( make_tuple(90,180,0) );
    tests.push_back( make_tuple(180,270,90) );
    tests.push_back( make_tuple(270,0,180) );
    tests.push_back( make_tuple(360,90,270) );
    tests.push_back( make_tuple(0.1,0,90) );

    for (auto test: tests){
        cout << "Testing: current_dir=" << get<0>(test) << ", expected_ccw=" << get<1>(test) << ", expected_cw=" << get<2>(test) << endl;

        model.target_direction = get<0>(test);
        select->exec();
        bool res = (model.target_direction == get<1>(test)) or (model.target_direction == get<2>(test));
        EXPECT_EQ(true, res);
    }

}

TEST_F(PerpendicularDirection_Tests, after_attack_directions){
    //current_dir, expected_dir
    vector<tuple<double,double>> tests;
    tests.push_back( make_tuple(5, 0) );
    tests.push_back( make_tuple(35, 0) );
    tests.push_back( make_tuple(87,90) );
    tests.push_back( make_tuple(99,90) );
    tests.push_back( make_tuple(131,90) );
    tests.push_back( make_tuple(135,90) );
    tests.push_back( make_tuple(136,180) );
    tests.push_back( make_tuple(115.77,90) );
    tests.push_back( make_tuple(300,270) );
    tests.push_back( make_tuple(330,0) );
    tests.push_back( make_tuple(331.65412,0) );
    tests.push_back( make_tuple(270.98542,270) );
    tests.push_back( make_tuple(0.98542,0) );
    //tests.push_back( make_tuple(0.1,0) );
    tests.push_back( make_tuple(359.98542,0) );

    for (auto test: tests){
        cout << "Testing: current_dir=" << get<0>(test) << ", expected_dir=" << get<1>(test) << endl;

        model.target_direction = get<0>(test);
        select->exec();

        EXPECT_EQ(model.target_direction, get<1>(test));
    }

}

#endif // TST_PERPENDICULAR_DIRECTION_H
