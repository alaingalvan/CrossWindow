#pragma once

#include "../Common/WindowDesc.h"

class NSWindow;
class NSApplication;
class NSAutoreleasePool;

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
	
	typedef MacWindow WindowDelegate;
}


