#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>


#include <QtWidgets>
#include "../src/playersm.h"

#include <iostream>
using namespace testing;
using namespace std;

class Collisions: public testing::Test {
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

    PlayerModel* model;

};

TEST_F(Collisions, debouncing)
{
    float start_x = 185;
    float start_y = 200;

    model = new PlayerModel {
            DEF_ENERGY, //energy
            normal, //state
            idle, //sub_state
            start_x, //pos_x
            start_y, //pos_y
            {false,true,false,true}, //direction
            0 // score
        };

    PlayerSm* cstate = new PlayerNormal(&*model);

    cout << "model x (before): " << model->pos_x << endl;
    cout << "model y (before): " << model->pos_y << endl;

    cstate->moveBy(15,15);

    cout << "model x (after step): " << model->pos_x << endl;
    cout << "model y (after step): " << model->pos_y << endl;

    QRectF m(200-15, //pos_x
             200-15, //pos_y
             30, //width
             30 //heigth
             );
    cout << "monster x : " << m.x() << endl;
    cout << "monster y : " << m.y() << endl;

    QRectF i = getIntersectonWith(m);
    cout << "intersection width: " << i.width() << endl;
    cout << "intersection height: " << i.height() << endl;

    if (not i.isEmpty()){
        double step = i.width();
        if(i.height()<i.width())
            step = i.height();
        cstate->moveBy(-step,-step);
        cstate->collisionWithMonster();
    }

    cout << "model x (after collision): " << model->pos_x << endl;
    cout << "model y (after collision): " << model->pos_y << endl;

    EXPECT_EQ(model->pos_x, start_x);
    EXPECT_EQ(model->pos_y, start_y);
}
