`CrossWindow-Graphics` is a helper library that can take a `xwin::Window` and graphics API specific data structures , and returning a Vulkan `vk::Surface`, an OpenGL context, a DirectX `ComPtr<IDXGISwapChain>`, or Metal `MTLView`. 

You can try out this demo in the [**CrossWindow-Demos** repo in the `/demos/graphics-api-seed/` folder](https://github.com/alaingalvan/crosswindow-demos/demos/graphics-api-seed/).

First we'll set up our project's dependencies in CMake.

```cmake
# We'll include CrossWindow and CrossWindow-Graphics as dependencies in our project.

# And we'll also include and dependencies related to the graphics APIs we may want to use.

# Finally we'll add preprocessor definitions for the graphics APIs we want.
```

We'll start things off as usual with CrossWindow.

```cpp
#include "CrossWindow/CrossWindow.h"
#include "CrossWindow/Graphics.h"

void xmain(int argc, const char** argv)
{
    // 🖼️ Create Window Description
    xwin::WindowDesc windowDesc;
    windowDesc.name = "Test";
    windowDesc.title = "My Title";
    windowDesc.visible = true;
    windowDesc.width = 1280;
    windowDesc.height = 720;

    bool closed = false;
    
    // ⚪ Initialize
    xwin::Window window;
    xwin::EventQueue eventQueue;

    if (!window.create(windowDesc, eventQueue))
    { return; }
```

Then initialize each graphics API:

```cpp
    // Initialize each graphics API


```

Create our graphics API specific data structures with CrossWindow:

```cpp

```

Then update them as usual while rendering:

```
    // 🏁 Engine loop
    bool isRunning = true;

    while (isRunning)
    {
        // ♻️ Update the event queue
        eventQueue.update();

        // 🎈 Iterate through that queue:
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
}
```