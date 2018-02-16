#pragma once

#if defined(XWIN_WINDOWS)
  #define MainArgsType HINSTANCE, HINSTANCE, LPSTR, int
  #define MainArgsVars hInstance, hPrevInstance, lpCmdLine, nCmdShow
  #define MainArgs HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow
  #define xmain int WINAPI WinMain
#elif defined(XWIN_ANDROID)
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