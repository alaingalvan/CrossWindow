#pragma once

#include "../Common/WindowDesc.h"
#include "../Common/Init.h"
#include "../Common/EventQueue.h"

#include <vector>

namespace xwin
{
	class MacWindow
	{
	public:
		MacWindow();
		
		~MacWindow();
		
		bool create(const WindowDesc& desc, EventQueue& eventQueue);
		
		void close();
		
		bool eventLoop();
		
	protected:
		//NSString*
		void* mTitle;

		//XWinWindow*
		void* mWindow;
		
		//XWinView*
		void* mView;
	};
	
	typedef MacWindow WindowDelegate;
}


