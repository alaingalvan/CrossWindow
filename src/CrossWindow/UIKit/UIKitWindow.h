#pragma once

#include "../Common/WindowDesc.h"
#include "../Common/Init.h"
#include "../Common/EventQueue.h"

namespace xwin
{
class Window
{
public:
	Window();
	
	~Window();
	
	bool update();
	
	enum class LayerType
	{
		Metal,
		OpenGL,
		LayerTypeMax
	};
	
	// Set the type of this window's view layer
	void setLayer(LayerType type);
	
	bool create(const WindowDesc& desc, EventQueue& eventQueue);
	
	void close();
	
	xwin::WindowDesc getDesc();
	
	
	//Any Layer Type
	void* layer;

	//XWinWindow*
	void* window;
	
	//XWinView*
	void* view;
	
	//XWinViewController*
	void* viewController;
	
	WindowDesc mDesc;
	
	xwin::EventQueue* mEventQueue;
	
};
}
