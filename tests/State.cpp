#include "gtest/gtest.h"
#include "CrossWindow/CrossWindow.h"

TEST(State, state)
{
  XWinState state = xwin::getXWinState();
	EXPECT_TRUE(sizeof(state) > 0);
}
