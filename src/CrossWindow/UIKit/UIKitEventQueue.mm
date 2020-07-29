#include "UIKitEventQueue.h"
#import <UIKit/UIKit.h>

namespace xwin
{
	void EventQueue::update()
	{
		// Update Application
		UIApplication* app = (UIApplication*)getXWinState().application;
	}
	
	const Event& EventQueue::front()
	{
		return mQueue.front();
	}
	
	void EventQueue::pop()
	{
		mQueue.pop();
	}
	
	bool EventQueue::empty()
	{
		return mQueue.empty();
	}
	
	
}
