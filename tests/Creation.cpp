#include "gtest/gtest.h"
#include "CrossWindow/CrossWindow.h"

TEST(Creation, create)
{
    // Create Window Object
    xwin::WindowDesc windowDesc;
    windowDesc.name = "Test";
    windowDesc.title = "My Title";
    windowDesc.visible = true;
    windowDesc.width = 1280;
    windowDesc.height = 720;

    xwin::Window window;
    xwin::EventQueue eventQueue;
	bool created = window.create(windowDesc, eventQueue);
	
	EXPECT_TRUE(created);
}
