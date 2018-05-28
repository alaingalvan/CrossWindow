#pragma once

#ifdef __linux__
#ifndef __ANDROID__
#include <xcb/xcb.h>
#endif
#endif

namespace mwin
{
	/**
	 * Linux Windows are XCB windows
	 * If demand for Wayland or Mir grows, a parameter XWIN_LINUX_PROTOCOL=AUTO 
	 * will default to XCB and users can set whatever windowing protocol they want.
	 */ 
	class LinuxWindow
	{
		LinuxWindow();

		bool create(WindowDesc& desc, EventQueue& eventQueue);
	};
	
	 typedef LinuxWindow WindowDelegate;
}
