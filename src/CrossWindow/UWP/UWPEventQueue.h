#pragma once

namespace xwin
{

namespace xwin
{
class Window;

class EventQueue
{
  public:
    EventQueue();

    void update();

    const Event& front();

    void pop();

    bool empty();

    EventQueueDelegate& getDelegate();

  protected:
    std::vector<Window*> windows;

    EventQueueDelegate mDelegate;
};
}
}