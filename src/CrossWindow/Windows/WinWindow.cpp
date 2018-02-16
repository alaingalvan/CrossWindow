#include "WinWindow.h"

namespace xwin
{
	WinWindow::WinWindow(const WindowDesc& desc)
	{
	};

	bool WinWindow::create(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
	{

		this->hInstance = hInstance;

		wndClass.cbSize = sizeof(WNDCLASSEX);
		wndClass.style = CS_HREDRAW | CS_VREDRAW;
		wndClass.lpfnWndProc = WinWindow::WindowProcStatic;
		wndClass.cbClsExtra = 0;
		wndClass.cbWndExtra = 0;
		wndClass.hInstance = hInstance;
		wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
		wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		wndClass.lpszMenuName = NULL;
		wndClass.lpszClassName = mDesc.name.c_str();
		wndClass.hIconSm = LoadIcon(NULL, IDI_WINLOGO);

		if (!RegisterClassEx(&wndClass))
		{
			fflush(stdout);
			exit(1);
		}

		int screenWidth = GetSystemMetrics(SM_CXSCREEN);
		int screenHeight = GetSystemMetrics(SM_CYSCREEN);

		if (desc.fullscreen)
		{
			DEVMODE dmScreenSettings;
			memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
			dmScreenSettings.dmSize = sizeof(dmScreenSettings);
			dmScreenSettings.dmPelsWidth = screenWidth;
			dmScreenSettings.dmPelsHeight = screenHeight;
			dmScreenSettings.dmBitsPerPel = 32;
			dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

			if ((desc.width != screenWidth) && (desc.height != screenHeight))
			{
				if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
				{
					if (MessageBox(NULL, "Fullscreen Mode not supported!\n Switch to window mode?", "Error", MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
					{
						desc.fullscreen = false;
					}
				}
			}

		}

		DWORD dwExStyle;
		DWORD dwStyle;


		if (desc.fullscreen)
		{
			dwExStyle = WS_EX_APPWINDOW;
			dwStyle = WS_POPUP | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
		}
		else
		{
			dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
			dwStyle = WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
		}

		RECT windowRect;
		windowRect.left = desc.x;
		windowRect.top = desc.y;
		windowRect.right = fullscreen ? (long)screenWidth : (long)desc.width;
		windowRect.bottom = fullscreen ? (long)screenHeight : (long)desc.height;

		AdjustWindowRectEx(&windowRect, dwStyle, FALSE, dwExStyle);

		_windowBeingCreated = this;
		_hwnd = CreateWindowEx(0,
			desc.name,
			desc.title,
			dwStyle | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
			0,
			0,
			windowRect.right - windowRect.left,
			windowRect.bottom - windowRect.top,
			NULL,
			NULL,
			hInstance,
			NULL);



		if (!fullscreen)
		{
			// Center on screen
			unsigned x = (GetSystemMetrics(SM_CXSCREEN) - windowRect.right) / 2;
			unsigned y = (GetSystemMetrics(SM_CYSCREEN) - windowRect.bottom) / 2;
			SetWindowPos(_hwnd, 0, x, y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		}

		if (!_hwnd)
		{
			printf("Could not create window!\n");
			fflush(stdout);
			exit(1);
		}

		if (desc.visible)
		{
			ShowWindow(_hwnd, SW_SHOW);
			SetForegroundWindow(_hwnd);
			SetFocus(_hwnd);
		}
	}

	LRESULT CALLBACK WinWindow::WindowProcStatic(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
	{
		WinWindow* _this;
		if (_windowBeingCreated != nullptr)
		{
			_hwndMap[hwnd] = _windowBeingCreated;
			_windowBeingCreated->_hwnd = hwnd;
			_this = _windowBeingCreated;
			_windowBeingCreated = nullptr;
		}
		else
		{
			auto existing = _hwndMap.find(hwnd);
			_this = existing->second;
		}

		return _this->WindowProc(msg, wparam, lparam);
	}

	LRESULT WinWindow::WindowProc(UINT msg, WPARAM wparam, LPARAM lparam)
	{
		// Propigate Events
		  // Call all input handler events with a struct of this signature.
		for (auto &handle : inputHandlers)
		{
			handle.event(_hwnd, msg, wparam, lparam);
		}
	}
}