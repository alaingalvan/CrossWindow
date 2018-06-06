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

  Key convertStringToKey(const char * str)
  {
      return Key();
  }

  FocusData::FocusData(bool focused) : focused(focused)
  {
  }

}