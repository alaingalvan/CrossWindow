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
		void* mWindow;
		void* mTitle;
	};
	
	typedef MacWindow WindowDelegate;
}


