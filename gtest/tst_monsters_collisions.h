#ifndef TST_MONSTERS_COLLISIONS_H
#define TST_MONSTERS_COLLISIONS_H
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>


#include <QtWidgets>
#include "../src/monster.h"

#include <iostream>
using namespace testing;
using namespace std;
namespace Monster {

class MonsterCollisions: public testing::Test {
public:

    QRectF getIntersectonWith(QRectF r)
    {
        int size = 30;
        QRectF me (model->pos_x-(size/2), model->pos_y-(size/2),
                size,size);
        cout << "me x : " << me.x() << endl;
        cout << "me y : " << me.y() << endl;
        QRectF b = me.intersected(r);
        return b;
    }

    MonsterModel* model;

};

TEST_F(MonsterCollisions, debouncing)
{

}

}
#endif // TST_MONSTERS_COLLISIONS_H
