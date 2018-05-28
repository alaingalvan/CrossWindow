#include "NoopEventQueue.h"

namespace xwin
{

  bool NoopEventQueue::update()
  {
    return false;
  }

  const Event& NoopEventQueue::front()
  {
    Event e(EventType::Close);

    return e;
  }

  void NoopEventQueue::pop()
  {
  }
}