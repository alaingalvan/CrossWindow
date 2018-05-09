

```cpp
#include "CrossWindow/CrossWindow.h"

void xmain(int argc, const char* argv[])
{
    // 🖼️ Create Window Description
    xwin::WindowDesc windowDesc;
    windowDesc.name = "Test";
    windowDesc.title = "My Title";
    windowDesc.visible = true;
    windowDesc.width = 1280;
    windowDesc.height = 720;

    // ⚪ Initialize
    std::vector<xwin::WindowPtr> windows = {new Window(), new Window()};
    for( xwin::WindowPtr& w : windows )
    { w->create(windowDesc); }

    // 🏁 Engine loop
    bool engineRunning = true;
    while( engineRunning )
    {
    for (auto itr = windows.begin(); itr != windows.end();)
    {
        bool closed = false;
        WindowPtr win = itr->window;
        auto events = win->pollEvents();
        for (xwin::EventType e : events)
        {
            // ↘️ Insert Applciation Logic Here:

            // 🔄 Check for events
            if (e == xwin::EventType::Close)
            {
                win->close();
                itr = windows.erase(itr);
                closed = true;
                break;
            }
        }
        if (!closed)
        {
            ++itr;
        }
    }
    }
  
  ```