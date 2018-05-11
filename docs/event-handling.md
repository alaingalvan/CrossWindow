While many other windowing libraries opt for a classical approach to event handling, where you would create a class that inherits their window, and overload virtual functions for different events, in CrossWindow we opt to use an **Event Queue**. 

```cpp
xwin::EventQueue eventQueue;
```

You can pass an event queue to a window for events from that window to be exposed to that eventQueue. This way you can either have 1 event queue that manages all events each window receives, or only listen to events from a specific Window by creating queues for each.

```cpp
bool isRunning = true;

while (isRunning)
{
  // Update the event queue with each window and the application's events
  eventQueue.update();

  // Iterate through that queue:
  while (!eventQueue.empty())
  {
    const xwin::Event event = eventQueue.pop();

    switch(event.type)
    {
    case xwin::EventType::MouseMove:
      xwin::MouseData* mouse = static_cast<xwin::MouseData*>(e.data);
      //mouse.x, mouse.y
      break;
    case xwin::EventType::Close:
      window.close();
    break;
    default:
      // Do nothing
    }
  }
}
```