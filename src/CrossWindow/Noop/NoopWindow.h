#pragma once

#include "../Common/WindowDesc.h"
#include "../Common/Init.h"
#include "../Common/EventQueue.h"

namespace xwin
{
	class NoopWindow
	{
		public:
		~NoopWindow();
		
		bool create(WindowDesc& desc, EventQueue& eventQueue);

		void close();
	};

	 typedef NoopWindow	WindowDelegate;
}
