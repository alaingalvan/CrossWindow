#include "gtest/gtest.h"
#include "CrossWindow/CrossWindow.h"

void xmain(int argc, const char** argv)
{
    ::testing::InitGoogleTest(&argc, (char**)argv);
    RUN_ALL_TESTS();
}
