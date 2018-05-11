First step is to create a initial window descriptor. 

```cpp
// 🖼️ Create Window Description
xwin::WindowDesc windowDesc;
windowDesc.name = "Test";
windowDesc.title = "My Title";
windowDesc.visible = true;
windowDesc.width = 1280;
windowDesc.height = 720;
```

The next step is to create an event Queue.

```cpp
xwin::EventQueue eventQueue;
```

Then pass that event queue to a `xwin::Window` object's create function.

```cpp

xwin::Window window;
bool success = window.create(windowDesc, eventQueue);
```

From there we can listen to events from that window by checking the event queue. To do this we'll want to set up a polling loop:

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
    // Do something with that event...
  }
}
```

For more details on the Event Queue, continue reading about [event handling](event-handling.md).