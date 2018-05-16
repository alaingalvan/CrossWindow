`CrossWindow-Graphics` is a helper library that can take a `xwin::Window` and graphics API specific data structures , and returning a Vulkan `vk::Surface`, an OpenGL context, a DirectX `ComPtr<IDXGISwapChain>`, or Metal `MTLView`. 

You can try out this demo in the [`demos/graphics-api-seed/`](/demos/graphics-api-seed/) folder.

```mm
//Since this includes C++ and Objective C++ according to preprocessor definitions
//We're using the `.mm` file type:

#include "CrossWindow/CrossWindow.h"

#if defined(XGFX_VULKAN)
#include "vulkan/vulkan.hpp"
#elif defined(XGFX_OPENGL)
#include "glad/glad.h"
#elif defined(XGFX_DIRECTX)
#include <directx12.h>
#elif defined(XGFX_METAL)
#import <Metal/Metal.h>
#endif

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

```mm
    // Initialize each graphics API

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

## OpenGL

For OpenGL we reccommend using 

```cpp
#include "CrossWindow/CrossWindow.h"
#include "glad/glad.h"

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

## DirectX 12

```cpp
#include "CrossWindow/CrossWindow.h"
#include ""
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

## Metal 2

**Note**, this example is in Objective C++:

```mm
#include "CrossWindow/CrossWindow.h"
#import <Metal/Metal.h>

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