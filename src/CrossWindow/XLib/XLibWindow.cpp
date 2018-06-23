#include "XLibWindow.h"

namespace xwin
{
  bool XLibWindow::create(WindowDesc& desc, EventQueue& eventQueue, Window* parent)
  {
    XInitThreads();
    demo->display = XOpenDisplay(NULL);
    long visualMask = VisualScreenMask;
    int numberOfVisuals;
    XVisualInfo vInfoTemplate={};
    vInfoTemplate.screen = DefaultScreen(demo->display);
    XVisualInfo *visualInfo = XGetVisualInfo(demo->display, visualMask,
                                             &vInfoTemplate, &numberOfVisuals);

    Colormap colormap = XCreateColormap(
                demo->display, RootWindow(demo->display, vInfoTemplate.screen),
                visualInfo->visual, AllocNone);

    XSetWindowAttributes windowAttributes={};
    windowAttributes.colormap = colormap;
    windowAttributes.background_pixel = 0xFFFFFFFF;
    windowAttributes.border_pixel = 0;
    windowAttributes.event_mask =
            KeyPressMask | KeyReleaseMask | StructureNotifyMask | ExposureMask;

    demo->xlib_window = XCreateWindow(
                demo->display, RootWindow(demo->display, vInfoTemplate.screen), 0, 0,
                demo->width, demo->height, 0, visualInfo->depth, InputOutput,
                visualInfo->visual,
                CWBackPixel | CWBorderPixel | CWEventMask | CWColormap, &windowAttributes);

    XSelectInput(demo->display, demo->xlib_window, ExposureMask | KeyPressMask);
    XMapWindow(demo->display, demo->xlib_window);
    XFlush(demo->display);
    demo->xlib_wm_delete_window =
XInternAtom(demo->display, "WM_DELETE_WINDOW", False);
  }

  bool XLibWindow::destroy()
  {
    XDestroyWindow(gfx::GetXDisplay(), window);
  }
}