#include "gtest/gtest.h"
#include "CrossWindow/CrossWindow.h"

#include <vector>

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

    std::vector<xwin::Event> e =
    {
        xwin::Event(xwin::EventType::Create, nullptr),
        xwin::Event(xwin::ResizeData(1280, 720), nullptr)
    };

}

