#include "gtest/gtest.h"
#include "CrossWindow/CrossWindow.h"


TEST(EventQueue, Update)
{

    xwin::EventQueue eventQueue;

    eventQueue.update();

    if (!eventQueue.empty())
    {
        const xwin::Event& e = eventQueue.front();
        eventQueue.pop();
    }
}

TEST(Events, Data)
{
    {
        xwin::Event e[1] =
        {
            xwin::Event(xwin::ResizeData(1280, 720))
        };

        //xwin::ResizeData d = e[0].getData();
    }
    // Event data should dealloc
}

