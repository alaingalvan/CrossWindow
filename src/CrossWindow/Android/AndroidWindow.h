#pragma once

#include <android/native_activity.h>
#include <android/asset_manager.h>
#include <android_native_app_glue.h>

namespace mwin
{
	class AndroidWindow
	{
		AndroidWindow();

		protected:
			ANativeWindow* mWindow;
	};
	
	 typedef AndroidWindow WindowDelegate;
}
