#pragma once

#ifdef XWIN_WINDOWS
#include <Windows.h>
#define xmain int WINAPI WinMain
#define MainArgs HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow
#define MainArgsVars hInstance, hPrevInstance, lpCmdLine, nCmdShow
#elif XWIN_ANDROID
#define MainArgsType android_app
#define MainArgsVars state
#define MainArgs android_app* state
#define xmain void android_main
#else
#define MainArgsType int, char**
#define MainArgsVars argc, argv
#define MainArgs int argc, char **argv
#define xmain int	main
#endif