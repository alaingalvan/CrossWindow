#pragma once

#include <string>

/**
  * Initial window description
  */
namespace xwin
{
  struct WindowDesc
  {
    // States
    bool visible;
    bool fullscreen;
    bool resizable;
    unsigned monitor;
    // App Data
    std::string title;
    std::string name;
    std::string iconPath;
    // Transform
    long x;
    long y;
    bool centered;
    unsigned width;
    unsigned height;

    WindowDesc();
  };

  enum class EventType : size_t
  {
      Close = 0,
      Resize,
      EventTypeMax
  };

  enum class DigitalInput : size_t
  {
      // keyboard
      // kKey must start at zero, see s_DXKeyMapping
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
      DPadUp,
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
}