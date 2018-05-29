#pragma once

#include <stddef.h>

namespace xwin
{
  enum class EventType : size_t
  {
      Close = 0,
      Resize,
      DigitalInput,
      AnalogInput,
      Mouse,
      Touch,
      Focus,
      Unfocus,
      EventTypeMax
  };

  enum class DigitalInput : size_t
  {
      // Keyboard
      Escape = 0,
      Num1,
      Num2,
      Num3,
      Num4,
      Num5,
      Num6,
      Num7,
      Num8,
      Num9,
      Num0,
      Minus,
      Equals,
      Back,
      Tab,
      Q,
      W,
      E,
      R,
      T,
      Y,
      U,
      I,
      O,
      P,
      LBracket,
      RBracket,
      Enter,
      LControl,
      A,
      S,
      D,
      F,
      G,
      H,
      J,
      K,
      L,
      Semicolon,
      Apostrophe,
      Grave,
      LShift,
      Backslash,
      Z,
      X,
      C,
      V,
      B,
      N,
      M,
      Comma,
      Period,
      slash,
      rshift,
      multiply,
      lalt,
      space,
      capital,
      F1,
      F2,
      F3,
      F4,
      F5,
      F6,
      F7,
      F8,
      F9,
      F10,
      Numlock,
      Scroll,
      Numpad7,
      Numpad8,
      Numpad9,
      Subtract,
      Numpad4,
      Numpad5,
      Numpad6,
      Add,
      Numpad1,
      Numpad2,
      Numpad3,
      Numpad0,
      Decimal,
      F11,
      F12,
      Numpadenter,
      RControl,
      Divide,
      sysrq,
      RAlt,
      Pause,
      Home,
      Up,
      PgUp,
      Left,
      Right,
      End,
      Down,
      PgDn,
      Insert,
      Del,
      LWin,
      RWin,
      Apps,

      DigitalInputKeysMax,

      // Gamepad
      DPadUp = DigitalInputKeysMax,
      DPadDown,
      DPadLeft,
      DPadRight,
      StartButton,
      BackButton,
      LThumbClick,
      RThumbClick,
      LShoulder,
      RShoulder,
      AButton,
      BButton,
      XButton,
      YButton,

      // Mouse
      Mouse0,
      Mouse1,
      Mouse2,
      Mouse3,
      Mouse4,
      Mouse5,
      Mouse6,
      Mouse7,

      DigitalInputMax
  };

  enum class AnalogInput : size_t
  {
      // gamepad
      AnalogLeftTrigger,
      AnalogRightTrigger,
      AnalogLeftStickX,
      AnalogLeftStickY,
      AnalogRightStickX,
      AnalogRightStickY,

      // mouse
      AnalogMouseX,
      AnalogMouseY,
      AnalogMouseScroll,

      AnalogInputsMax
  };
	
	class Event
	{
    public:
        
        Event(EventType type, void* data = nullptr);

        ~Event();

        // The event's type
		EventType type;

        // Pointer to a CrossWindow event data type, is destroyed when the event is destructed.
		void* data;
	};

    class ResizeData
    {
    public:
        unsigned width;
        unsigned height;
        ResizeData(unsigned width, unsigned height);
    };

    class DigitalInputData
    {
        public:
        DigitalInput key;
        DigitalInputData(DigitalInput key);
    };
}