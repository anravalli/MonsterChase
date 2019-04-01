#include "tst_collisions.h"
#include "tst_arena.h"

#include <gtest/gtest.h>
#include <QApplication>

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);

    QApplication a(argc, argv);

    return RUN_ALL_TESTS();
}
