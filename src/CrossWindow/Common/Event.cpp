#include "Event.h"

namespace xwin
{
  Event::Event(EventType type) : type(type)
  {}

  Event::Event(FocusData data) : type(EventType::Focus)
  {
      _data.focus = data;
  }

  Event::Event(ResizeData data) : type(EventType::Resize)
  {
      _data.resize = data;
  }

  Event::Event(KeyboardData data) : type(EventType::Keyboard)
  {
      _data.keyboard = data;
  }

  Event::Event(MouseMoveData data) : type(EventType::MouseMoved)
  {
      _data.mouseMoved = data;
  }

  Event::Event(MouseInputData data) : type(EventType::MouseInput)
  {
      _data.mouseInput = data;
  }

  Event::Event(MouseWheelData data) : type(EventType::MouseWheel)
  {
      _data.mouseWheel = data;
  }

  Event::Event(TouchData data) : type(EventType::Touch)
  {
      _data.touch = data;
  }

  Event::Event(GamepadData data) : type(EventType::Gamepad)
  {
      _data.gamepad = data;
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