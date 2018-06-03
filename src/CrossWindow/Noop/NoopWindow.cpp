#include "NoopWindow.h"

namespace xwin
{
  bool NoopWindow::create(WindowDesc& desc, EventQueue& eventQueue)
  {
    return true;
  }
  void NoopWindow::close()
  {
  }
}