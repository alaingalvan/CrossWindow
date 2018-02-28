#pragma once

#include "../Common/WindowDesc.h"

#include <Cocoa/Cocoa.h>

namespace xwin
{
	class MacWindow
	{
	public:
		MacWindow();
		
		~MacWindow();
		
		bool create(const WindowDesc& desc);
		
		void destroy();
		
		bool eventLoop();
		
	protected:
		NSAutoreleasePool* pool;
		NSApplication* app;
		NSWindow* window;
	};
}
