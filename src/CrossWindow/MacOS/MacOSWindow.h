#pragma once

#include "../Common/WindowDesc.h"
#include "../Common/Init.h"
#include <vector>

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

		//XWinWindow*
		void* mWindow;
		
		//XWinView*
		void* mView;
	};
	
	typedef MacWindow WindowDelegate;
}


