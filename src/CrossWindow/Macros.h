#pragma once

#if defined(_WIN32)
  #define MainArgsType HINSTANCE, HINSTANCE, LPSTR, int
  #define MainArgsVars hInstance, hPrevInstance, lpCmdLine, nCmdShow
  #define MainArgs HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow
  #define xmain int WINAPI WinMain
#elif defined(__ANDROID__)
  #define MainArgsType android_app
  #define MainArgsVars state
  #define MainArgs android_app* state
  #define xmain void android_main
#elif defined(__APPLE__) || defined(__linux__) ||defined(MAG_NOOP)
  #define MainArgsType int, char**
  #define MainArgsVars argc, argv
  #define MainArgs int argc, char **argv
  #define xmain int	main
#endif