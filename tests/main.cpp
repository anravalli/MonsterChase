#include "tst_player_collisions.h"
#include "tst_arena.h"
#include "tst_linear_rotation.h"
#include "tst_monsters_collisions.h"
#include "tst_monster_player_detection.h"

#include <gtest/gtest.h>
#include <QApplication>

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);

    QApplication a(argc, argv);

    return RUN_ALL_TESTS();
}
