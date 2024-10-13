#pragma once

#ifndef __BASERENDERWINDOW_H__
#define __BASERENDERWINDOW_H__

#ifndef UNICODE
#define UNICODE
#endif

#include "memoryimage.h"
#include "point.h"
#include <windows.h>

namespace sr {

class BaseRenderWindow {
protected:
    MemoryImage img;
    const wchar_t* title;
    HWND hwnd;
    HINSTANCE hInstance;
    static const wchar_t* ClassName();
    static LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    void Register();
    void Create();
    void Show();
public:
    BaseRenderWindow(const wchar_t *title, int width, int height);
    void show();
    void clear(const Color &color);
    int getWidth() const;
    int getHeight() const;
    void setPixel(const Point &point, const Color &color);
    Color getPixel(const Point &point) const;
};

} // namespace sr

#endif // #ifndef __BASERENDERWINDOW_H__