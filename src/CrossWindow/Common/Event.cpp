#include "Event.h"

namespace xwin
{
  Event::Event(EventType type, void* data) : type(type), data(data)
  {}

  Event::~Event()
  {
    if( data != nullptr)
    {
      delete data;
      data = nullptr;
    }
  }

  DigitalInputData::DigitalInputData(DigitalInput key) : key(key)
  {
  }

  ResizeData::ResizeData(unsigned width, unsigned height) : width(width), height(height)
  {
  }

}