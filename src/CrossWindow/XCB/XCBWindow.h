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
	 */ 
	class XCBWindow
	{
		XCBWindow();

		bool create(WindowDesc& desc, EventQueue& eventQueue);
	};
	
	 typedef XCBWindow WindowDelegate;
}
