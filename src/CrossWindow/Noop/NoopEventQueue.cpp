#include "NoopEventQueue.h"

namespace xwin
{

  bool NoopEventQueue::update()
  {
    return false;
  }

  const Event& NoopEventQueue::front()
  {
    e = Event(EventType::Close);
    return e;
  }

  void NoopEventQueue::pop()
  {
  }
}