#include "UIKitEventQueue.h"
#import <UIKit/UIKit.h>

namespace xwin
{
void EventQueue::update()
{
	// Update Application
	UIApplication* app = (UIApplication*)getXWinState().application;
	while( CFRunLoopRunInMode(kCFRunLoopDefaultMode, 0.0001, true) == kCFRunLoopRunHandledSource);
}

void EventQueue::pushEvent(Event e)
{
	mQueue.push(e);
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
