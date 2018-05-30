#pragma once

#include "../Common/Event.h"
#include <Windows.h>
#include <queue>

namespace xwin
{
  class Win32EventQueue
  {
public:
  Win32EventQueue();

  bool update();

  const Event& front();

  void pop();

  bool empty();


protected:

  void pushEvent(MSG msg);

  std::queue<Event> mQueue;
  };

  typedef Win32EventQueue EventQueueDelegate;
}