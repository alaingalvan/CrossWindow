#pragma once


#include <Windows.h>
#include <unordered_map>
#include "../Common/WindowDesc.h"
#include "../CrossWindow.h"

namespace mwin
{
	class WinWindow
	{

		WinWindow(WindowDesc desc);

		static LRESULT CALLBACK WindowProcStatic(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

		LRESULT WindowProc(UINT msg, WPARAM wparam, LPARAM lparam);

	private:
	  // Application Handle
		HINSTANCE hInstance;

		// Window Handle
		HWND _hwnd;

		// Window State
		WNDCLASSEX wndClass;

		// Window Size/Position
		RECT windowRect;

		// Screen State
		DEVMODE dmScreenSettings;

    // Window Behavior
		DWORD dwExStyle;
	  DWORD dwStyle;
		
		static thread_local WinWindow* _windowBeingCreated;
		static thread_local std::unordered_map<HWND, WinWindow*> _hwndMap;
	};

	 typedef WinWindow WindowDelegate;
}
