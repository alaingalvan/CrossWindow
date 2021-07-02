#pragma once

namespace mwin
{
	class Window
	{
		Window();

		bool create(const WindowDesc& desc, EventQueue& eventQueue);

		bool destroy();
	};
}
