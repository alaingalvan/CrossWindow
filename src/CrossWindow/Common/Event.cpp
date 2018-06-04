#include "Event.h"

namespace xwin
{
  Event::Event(EventType type) : type(type)
  {}

  Event::Event(ResizeData data) : type(EventType::Resize)
  {
      _data.resize = data;
  }

  Event::Event(MouseData data) : type(EventType::Mouse)
  {
      _data.mouse = data;
  }


  Event::Event(DigitalInputData data) : type(EventType::DigitalInput)
  {
      _data.digitalInput = data;
  }

  Event::~Event()
  {
  }

  DigitalInputData::DigitalInputData(DigitalInput key) : key(key)
  {
  }

  ResizeData::ResizeData(unsigned width, unsigned height) : width(width), height(height)
  {
  }

}