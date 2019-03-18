#pragma once

#include <Windows.h>

#include "../Common/Event.h"

#include <queue>

namespace xwin
{
class Window;

class Win32EventQueue
{
  public:
    Win32EventQueue();

    void update();

    const Event& front();

    void pop();

    bool empty();

    void pushEvent(MSG msg, Window* window);

  protected:
    bool initialized;

    unsigned prevMouseX;
    unsigned prevMouseY;

    std::queue<Event> mQueue;

    /**
     * Virtual Key Codes in Win32 are an unsigned char:
     * https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731%28v=vs.85%29.aspx?f=255&MSPPError=-2147217396
     */
    typedef Key Win32VKeyToDigitalInputMap[1 << (8 * sizeof(unsigned char))];

    Win32VKeyToDigitalInputMap mVKeyToDigitalInputMap = {
        /*NONE 0x00*/ Key::KeysMax,
        /*VK_LBUTTON 0x01*/ Key::KeysMax,
        /*VK_RBUTTON 0x02*/ Key::KeysMax,
        /*VK_CANCEL 0x03*/ Key::KeysMax};
};

typedef Win32EventQueue EventQueueDelegate;
}