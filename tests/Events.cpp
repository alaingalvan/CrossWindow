#include "gtest/gtest.h"
#include "CrossWindow/CrossWindow.h"


TEST(EventQueue, Update)
{
  
  xwin::EventQueue eventQueue;

  eventQueue.update();

  eventQueue.front();

  eventQueue.pop();
}

TEST(Events, DigitalInput)
{
  {
    xwin::Event e( xwin::EventType::DigitalInput, new xwin::DigitalInputData(DigitalInput::Z));
  }
  // Event data should dealloc
}

