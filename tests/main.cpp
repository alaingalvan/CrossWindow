#include "gtest/gtest.h"
#include "CrossWindow/CrossWindow.h"

void xmain(int argc, const char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}