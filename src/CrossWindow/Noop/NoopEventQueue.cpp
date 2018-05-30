#include "NoopEventQueue.h"

namespace xwin
{
  NoopEventQueue::NoopEventQueue()
  {
  }

  bool NoopEventQueue::update()
  {
    return false;
  }

  const Event& NoopEventQueue::front()
  {
    return e;
  }

  void NoopEventQueue::pop()
  {
  }
}