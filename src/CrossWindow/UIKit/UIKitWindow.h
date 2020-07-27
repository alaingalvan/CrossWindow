#pragma once

namespace xwin
{
  class Window
  {
  public:
	  bool update();
	  
    protected:
    void* mWindow;
  };
}
