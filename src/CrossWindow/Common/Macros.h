#pragma once

#ifdef XWIN_WINDOWS
#include <Windows.h>
#elif XWIN_MACOS
#import <Cocoa/Cocoa.h>
#elif XWIN_LINUX

#elif XWIN_ANDROID
#include <android/log.h>
#include <dlfcn.h>
#elif XWIN_IOS
#import <UIKit/UIKit.h>
#endif

#ifdef XWIN_WINDOWS
#define xmain int WINAPI WinMain
#define MainArgs HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow
#define MainArgsVars hInstance, hPrevInstance, lpCmdLine, nCmdShow
#elif XWIN_ANDROID
#define xmain void android_main
#define MainArgs android_app* state
#define MainArgsVars state
#elif XWIN_LINUX || XWIN_MACOS || XWIN_IOS || XWIN_WASM
#define xmain int main
#define MainArgs int argc, const char* argv[]
#define MainArgsVars argc, argv
#endif