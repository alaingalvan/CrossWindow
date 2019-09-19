#pragma once

#include "../Common/WindowDesc.h"
#include "../Common/Init.h"
#include "../Common/EventQueue.h"

#include <vector>

namespace xwin
{
	class Window;

	class CocoaWindow
	{
	public:
		CocoaWindow();
		
		~CocoaWindow();
		
		bool create(const WindowDesc& desc, EventQueue& eventQueue, Window* parent);
		
		void close();
		
		bool eventLoop();
		
		void setMousePosition(unsigned x, unsigned y);
		
		UVec2 getCurrentDisplaySize();
		
		enum class LayerType
		{
			Metal,
			LayerTypeMax
		};
		
		// Set the type of this window's view layer
		void setLayer(LayerType type = LayerType::Metal);
		
		//XWinWindow*
		void* window;
		
		//XWinView*
		void* view;
		
		//Any Layer Type
		void* layer;
		
	protected:
		//NSString*
		void* mTitle;

		/**
		 * MacOS Keycodes: 
		 * https://stackoverflow.com/questions/3202629/where-can-i-find-a-list-of-mac-virtual-key-codes
		 */
  typedef Key MacKeycodeToDigitalInputMap[1 << (8 * sizeof(unsigned char))];


	};
	
	typedef CocoaWindow WindowDelegate;
}


