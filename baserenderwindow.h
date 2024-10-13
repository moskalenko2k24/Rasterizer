#pragma once

#ifndef __BASERENDERWINDOW_H__
#define __BASERENDERWINDOW_H__

#ifndef UNICODE
#define UNICODE
#endif

#include "ibaserenderwindow.h"
#include "memoryimage.h"
#include "point.h"
#include <windows.h>

namespace sr {

class BaseRenderWindow: public IBaseRenderWindow {
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
    void show() override;
    void clear(const Color &color) override;
    int getWidth() const override;
    int getHeight() const override;
    void setPixel(const Point &point, const Color &color) override;
    Color getPixel(const Point &point) const override;
};

} // namespace sr

#endif // #ifndef __BASERENDERWINDOW_H__
