#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "../src/player.h"

using namespace testing;

TEST(Collisoins, debouncing)
{
    QGraphicsScene* scene = new QGraphicsScene();
    Player p(scene);

    EXPECT_EQ(1, 1);
    ASSERT_THAT(0, Eq(0));
}
