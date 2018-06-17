#pragma once

namespace mwin
{
	class XLibWindow
	{
		XLibWindow();

		bool create(WindowDesc& desc, EventQueue& eventQueue, Window* parent);
	};
	
	 typedef XLibWindow WindowDelegate;
}
