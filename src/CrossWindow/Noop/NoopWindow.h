#pragma once

#include "../Common/WindowDesc.h"
#include "../Common/Init.h"
#include "../Common/EventQueue.h"

namespace xwin
{
	class Window;

	class NoopWindow
	{
		public:
		~NoopWindow();
		
		bool create(WindowDesc& desc, EventQueue& eventQueue, Window* parent);

		void close();
	};

	 typedef NoopWindow	WindowDelegate;
}
