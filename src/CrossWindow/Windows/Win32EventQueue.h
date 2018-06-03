#pragma once

#include "../Common/Event.h"
#include <Windows.h>
#include <queue>

namespace xwin
{
  class Win32EventQueue
  {
public:
  Win32EventQueue();

  bool update();

  const Event& front();

  void pop();

  bool empty();


protected:

  void pushEvent(MSG msg);

  std::queue<Event> mQueue;

  /**
   * Virtual Key Codes in Win32 are an unsigned char:
   * https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731%28v=vs.85%29.aspx?f=255&MSPPError=-2147217396
   */ 
  typedef DigitalInput Win32VKeyToDigitalInputMap[1 << (8 * sizeof(unsigned char))];

  Win32VKeyToDigitalInputMap mVKeyToDigitalInputMap = 
  {
    /*NONE 0x00*/ DigitalInput::DigitalInputKeysMax,
    /*VK_LBUTTON 0x01*/ DigitalInput::Mouse0,
    /*VK_RBUTTON 0x02*/ DigitalInput::Mouse1,
    /*VK_CANCEL 0x03*/ DigitalInput::DigitalInputKeysMax
  };
  };

  typedef Win32EventQueue EventQueueDelegate;
}