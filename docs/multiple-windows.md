

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
    xwin::EventQueue eventQueue;
    std::vector<xwin::WindowPtr> windows = {new Window(), new Window()};
    for( xwin::WindowPtr& w : windows )
    { w->create(windowDesc, eventQueue); }

    // 🏁 Engine loop
    bool engineRunning = true;
    while( engineRunning )
    {

        // ↘️ Insert Applciation Logic Here:

        // ♻️ And update windows

        eventQueue.update();

        // Iterate through that queue:
        while (!eventQueue.empty())
        {
            const xwin::Event event = eventQueue.pop();

            switch(e.type)
            {
            case xwin::EventType::Close:
                // Close the window
                event.window.close();
                
                // Deallocate the Window
                windows.erase(event.window);

                // Clear the weak pointer to that window from the queue
                eventQueue.erase(event.window);
            break;
            default:
                // Do nothing
            }
        }
        
        if(windows.empty())
        {
            engineRunning = false;
        }
    }
  
  ```