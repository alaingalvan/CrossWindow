#include "WinEventQueue.h"

namespace xwin
{
  bool WinEventQueue::update()
  {
    MSG msg = {};
    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
      //Translate virtual key messages
      TranslateMessage(&msg);

      //push to abstract event queue
      pushEvent(msg);

      //dispatch events to their coresponding windows
      DispatchMessage(&msg);

    }

    return true;
  }

  void WinEventQueue::pushEvent(MSG msg)
  {
    UINT message = msg.message;

    switch(message)
    {
        case WM_CREATE:

            break;
        case WM_SETFOCUS:

            break;
        case WM_KILLFOCUS:

            break;
        case WM_KEYDOWN:

            DigitalInput d;
        
            switch (msg.wParam)
            {
                case VK_UP:
                d = DigitalInput::Up;
                break;
                case VK_DOWN:
                d = DigitalInput::Down;
                break;
            }

            mQueue.emplace(EventType::DigitalInput, new DigitalInputData(d));
            break;
        case WM_SIZE:
            unsigned width, height;
            width = (unsigned)(UINT)(UINT64)msg.lParam & 0xFFFF;
            height = (unsigned)(UINT)(UINT64)msg.lParam >> 16;

            mQueue.emplace(EventType::Resize, new ResizeData(width, height));
            break;

        case WM_DESTROY:
            mQueue.emplace(xwin::EventType::Close);
            break;
      default:
      // Do nothing
          break;
    }
  }

  const Event& WinEventQueue::front()
  {
      return mQueue.front();
  }

  void WinEventQueue::pop()
  {
      mQueue.pop();
  }

  bool WinEventQueue::empty()
  {
      return mQueue.empty();
  }
}