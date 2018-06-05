#include "gtest/gtest.h"
#include "CrossWindow/CrossWindow.h"


TEST(EventQueue, Update)
{
  
  xwin::EventQueue eventQueue;

  eventQueue.update();

  if (!eventQueue.empty() )
  { 
      const xwin::Event& e = eventQueue.front();
      eventQueue.pop();
  }
}

TEST(Events, Data)
{
  {
    xwin::Event digitalEvent(xwin::DigitalInputData());

    xwin::ResizeData(1280, 720);
  }
  // Event data should dealloc
}

