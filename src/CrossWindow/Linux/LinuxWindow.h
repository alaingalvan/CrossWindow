#pragma once

#ifdef __linux__
#ifndef __ANDROID__
#include <xcb/xcb.h>

namespace mwin
{
	class LinuxWindow
	{
		LinuxWindow();
	}
	
	 typedef LinuxWindow WindowDelegate;
}
