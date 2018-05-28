#pragma once

namespace xwin
{
	class NoopWindow
	{
		public:
		bool create(WindowDesc& desc, EventQueue& eventQueue);
	};

	 typedef NoopWindow	WindowDelegate;
}
