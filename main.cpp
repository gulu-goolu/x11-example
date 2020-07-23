#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>

enum {
  RECT_X = 20,
  RECT_Y = 20,
  RECT_WIDTH = 10,
  RECT_HEIGHT = 10,

  WIN_X = 10,
  WIN_Y = 10,
  WIN_WIDTH = 100,
  WIN_HEIGHT = 100,
  WIN_BORDER = 1,
};

int main() {
  Display *display = nullptr;
  Window window;
  XEvent event;
  int screen = 0;

  display = XOpenDisplay(nullptr);
  if (display == nullptr) {
    fprintf(stderr, "Cannot open display\n");
    exit(1);
  }

  screen = DefaultScreen(display);

  window = XCreateSimpleWindow(
      display, RootWindow(display, screen), WIN_X, WIN_Y, WIN_WIDTH, WIN_HEIGHT,
      WIN_BORDER, BlackPixel(display, screen), WhitePixel(display, screen));

  Atom del_window = XInternAtom(display, "WM_DELETE_WINDOW", 0);
  XSetWMProtocols(display, window, &del_window, 1);

  XSelectInput(display, window, ExposureMask | KeyPressMask);

  XMapWindow(display, window);

  while (true) {
    XNextEvent(display, &event);

    switch (event.type) {
      case KeyPress:
      case ClientMessage:
        goto breakout;
      case Expose:
        XFillRectangle(display, window, DefaultGC(display, screen), RECT_X,
                       RECT_Y, RECT_WIDTH, RECT_HEIGHT);
    }
  }
breakout:
  XDestroyWindow(display, window);
  XCloseDisplay(display);

  return 0;
}
