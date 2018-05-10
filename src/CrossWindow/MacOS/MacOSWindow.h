#pragma once

#include "../Common/WindowDesc.h"

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
		//NSString*
		void* mTitle;

		//NSWindow*
		void* mWindow;
		
		//NSView*
		void* mView;
	};
	
	typedef MacWindow WindowDelegate;
}


