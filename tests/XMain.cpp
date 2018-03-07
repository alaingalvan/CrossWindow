#include "gtest/gtest.h"
#include "CrossWindow/CrossWindow.h"

void xmain(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
}
