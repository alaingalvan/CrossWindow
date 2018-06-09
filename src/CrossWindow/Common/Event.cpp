#include "Event.h"

namespace xwin
{
  Event::Event(EventType type) : type(type)
  {}

  Event::Event(FocusData d) : type(EventType::Focus)
  {
      data.focus = d;
  }

  Event::Event(ResizeData d) : type(EventType::Resize)
  {
      data.resize = d;
  }

  Event::Event(KeyboardData d) : type(EventType::Keyboard)
  {
      data.keyboard = d;
  }

  Event::Event(MouseMoveData d) : type(EventType::MouseMoved)
  {
      data.mouseMoved = d;
  }

  Event::Event(MouseInputData d) : type(EventType::MouseInput)
  {
      data.mouseInput = d;
  }

  Event::Event(MouseWheelData d) : type(EventType::MouseWheel)
  {
      data.mouseWheel = d;
  }

  Event::Event(TouchData d) : type(EventType::Touch)
  {
      data.touch = d;
  }

  Event::Event(GamepadData d) : type(EventType::Gamepad)
  {
      data.gamepad = d;
  }

  Event::~Event()
  {
  }

  ResizeData::ResizeData(unsigned width, unsigned height) : width(width), height(height)
  {
  }

  const char * convertKeyToString(Key key)
  {
      return nullptr;
  }

  Key convertStringToKey(const char* str)
  {
      return Key();
  }

  FocusData::FocusData(bool focused) : focused(focused)
  {
  }

  ModifierState::ModifierState(bool ctrl, bool alt, bool shift, bool meta) : ctrl(ctrl), alt(alt), shift(shift), meta(meta)
  {
  }

  MouseMoveData::MouseMoveData(unsigned x, unsigned y, ModifierState modifiers) : x(x), y(y), modifiers(modifiers)
  {
  }

  MouseInputData::MouseInputData(MouseInput button, ButtonState state, ModifierState modifiers) : button(button), state(state), modifiers(modifiers)
  {
  }

  KeyboardData::KeyboardData(Key key, ButtonState state, ModifierState modifiers) : key(key), state(state), modifiers(modifiers)
  {
  }

  MouseWheelData::MouseWheelData(double delta, ModifierState modifiers) : delta(delta), modifiers(modifiers)
  {
  }

}