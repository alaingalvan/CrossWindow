#include "Window.h"

#if defined(MAG_NOOP)
	#include "Noop/NoopWindow.h"
#elif defined(_WIN32)
	#include "../Windows/WinWindow.h"
#elif defined(__APPLE__)
	#include "TargetConditionals.h"
	#if TARGET_OS_IPHONE
		#include "iOS/iOSWindow.h"
	#else
		#define TARGET_OS_OSX 1
		#include "../MacOS/MacOSWindow.h"
	#endif
#elif defined(__ANDROID__)
	#include "../Android/AndroidWindow.h"
#elif defined(__linux__)
	#include "../Linux/LinuxWindow.h"
#endif

namespace mwin
{
	Window::Window(WindowDesc desc, MainArgs) : desc(desc)
	{
		mMainArgs = std::make_tuple(MainArgs);
		delegate.create(desc, mMainArgs);
	}

	Window::Window(WindowDesc desc) : desc(desc)
	{
		if (mMainArgs)
		{
			delegate.create(desc, mMainArgs);
		}
		else
		{
			//exit(1);
		}
	}
}