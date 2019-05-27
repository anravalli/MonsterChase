#ifndef TST_MONSTER_PLAYER_DETECTION_H
#define TST_MONSTER_PLAYER_DETECTION_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>


#include <QtWidgets>
#include "../src/monster.h"
#include "../src/behaviors.h"

#include <iostream>
using namespace testing;
using namespace std;

namespace Monster {

//class DummyMonster: public Monster {
//public:
//    DummyMonster():
//        Monster()
//    {
//    }

//    void setDir(double d){
//        model.direction = d;
//    }

//    pair<double,double> getPos(){
//        auto pos = make_pair(model.pos_x,model.pos_y);
//        return pos;
//    }

//    void setPos(pair<double,double> pos){
//        model.pos_x = pos.first;
//        model.pos_y = pos.second;
//        return;
//    }


//private:
//    //WallsCollisionChecker* _checker;
//};

class SightCollisionDetection_Test: public testing::Test {
public:

    void SetUp (){

    }

    void TearDown(){

    }

};

TEST_F(SightCollisionDetection_Test, repositioning){
    DummyMonster monster;

    monster.setPos(make_pair(0,0));
    monster.setDir(0);

    QRectF test_rect = QRectF(-65, -165, 130, 150);
    test_rect.moveTo(0-65,0-165);
    QRectF sight_box = monster.sightBox();
    EXPECT_EQ(test_rect.topLeft().x(), sight_box.topLeft().x());
    EXPECT_EQ(test_rect.topLeft().y(), sight_box.topLeft().y());
    EXPECT_EQ(test_rect.topRight().x(), sight_box.topRight().x());
    EXPECT_EQ(test_rect.topRight().y(), sight_box.topRight().y());
    EXPECT_EQ(test_rect.bottomLeft().x(), sight_box.bottomLeft().x());
    EXPECT_EQ(test_rect.bottomLeft().y(), sight_box.bottomLeft().y());
    EXPECT_EQ(test_rect.bottomRight().x(), sight_box.bottomRight().x());
    EXPECT_EQ(test_rect.bottomRight().y(), sight_box.bottomRight().y());

}

TEST_F(SightCollisionDetection_Test, intersection){
    DummyMonster monster;

    monster.setPos(make_pair(0,0));
    monster.setDir(0);

    QRectF test_rect = QRectF(-15, -15, 30, 30);
    test_rect.moveTo(0,0);
    QRectF sight_box = monster.sightBox();

    cout << "test_rect.topLeft().x(): " << test_rect.topLeft().x() << "; sight_box.topLeft().x() " << sight_box.topLeft().x() << endl;
    cout << "test_rect.topLeft().y(): " << test_rect.topLeft().y() << "; sight_box.topLeft().y() " <<  sight_box.topLeft().y() << endl;
    cout << "test_rect.topRight().x(): " << test_rect.topRight().x() << "; sight_box.topRight().x() " <<  sight_box.topRight().x() << endl;
    cout << "test_rect.topRight().y(): " << test_rect.topRight().y() << "; sight_box.topRight().y() " <<  sight_box.topRight().y() << endl;
    cout << "test_rect.bottomLeft().x(): " << test_rect.bottomLeft().x() << "; sight_box.bottomLeft().x() " <<  sight_box.bottomLeft().x() << endl;
    cout << "test_rect.bottomLeft().y(): " << test_rect.bottomLeft().y() << "; sight_box.bottomLeft().y() " <<  sight_box.bottomLeft().y() << endl;
    cout << "test_rect.bottomRight().x(): " << test_rect.bottomRight().x() << "; sight_box.bottomRight().x() " <<  sight_box.bottomRight().x() << endl;
    cout << "test_rect.bottomRight().y(): " << test_rect.bottomRight().y() << "; sight_box.bottomRight().y() " <<  sight_box.bottomRight().y() << endl;

    BehaviorStatus status = fail;
    QRectF i = sight_box.intersected(test_rect);
    if (not i.isEmpty()){
        status = success;
    }
    EXPECT_EQ(i.isEmpty(), false);
    EXPECT_EQ(status, success);
}

}
#endif // TST_MONSTER_PLAYER_DETECTION_H
