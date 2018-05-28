#pragma once

namespace xwin
{
  class AndroidEventQueue
  {
    bool update();
  };

  typedef AndroidEventQueue EventQueueDelegate;
}