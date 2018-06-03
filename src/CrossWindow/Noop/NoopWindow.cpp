#include "NoopWindow.h"

namespace xwin
{
  NoopWindow::~NoopWindow()
  {
    close();
  }

  bool NoopWindow::create(WindowDesc& desc, EventQueue& eventQueue)
  {
    return true;
  }
  void NoopWindow::close()
  {
  }
}