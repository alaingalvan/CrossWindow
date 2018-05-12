<!--We distribute an official library for hooking CrossWindow to your operating system specific operating system.-->

## Vulkan

For this example we'll use the Vulkan C++ library:

```cpp
#include "CrossWindow/CrossWindow.h"
#include "vulkan/vulkan.hpp"

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