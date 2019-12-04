#include "gtest/gtest.h"
#include "CrossWindow/CrossWindow.h"

TEST(State, state)
{
    xwin::XWinState state = xwin::getXWinState();
    bool t = sizeof(state) > 0;
    EXPECT_TRUE(t);
}
