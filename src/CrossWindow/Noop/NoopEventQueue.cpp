#include "NoopEventQueue.h"

namespace xwin
{
  NoopEventQueue::NoopEventQueue()
  {
  }

  void NoopEventQueue::update()
  {
  }

  const Event& NoopEventQueue::front()
  {
    return e;
  }

  void NoopEventQueue::pop()
  {
  }
  bool NoopEventQueue::empty()
  {
	  return false;
  }
}