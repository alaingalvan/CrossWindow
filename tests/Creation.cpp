#include "gtest/gtest.h"
#include "CrossWindow/CrossWindow.h"

TEST(Creation, Create)
{
    // Create Window Object
    xwin::WindowDesc windowDesc;
    windowDesc.name = "TestCreation";
    windowDesc.title = "My Title";
    windowDesc.visible = true;
    windowDesc.width = 1280;
    windowDesc.height = 720;

    xwin::Window window;
    xwin::EventQueue eventQueue;

    bool created = window.create(windowDesc, eventQueue);
    //EXPECT_TRUE(created);
}

TEST(Creation, Description)
{
    // Create Window Object
    xwin::WindowDesc windowDesc;
    windowDesc.name = "TestDescription";
    windowDesc.title = "My Title";
    windowDesc.visible = true;
    windowDesc.width = 1280;
    windowDesc.height = 720;

    xwin::Window window;
    xwin::EventQueue eventQueue;
	window.create(windowDesc, eventQueue);
    eventQueue.update();

    xwin::WindowDesc desc = window.getDesc();
	EXPECT_TRUE(desc.width == windowDesc.width);
}

TEST(Creation, Delgates)
{
    // Create Window Object
    xwin::WindowDesc windowDesc;
    windowDesc.name = "TestDelegate";
    windowDesc.title = "My Title";
    windowDesc.visible = true;
    windowDesc.width = 1280;
    windowDesc.height = 720;

    xwin::Window window;
    xwin::EventQueue eventQueue;
	window.create(windowDesc, eventQueue);
    eventQueue.update();
    xwin::WindowDelegate& delegate = window.getDelegate();
}