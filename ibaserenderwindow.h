#pragma once

#ifndef __IBASERENDERWINDOW_H__
#define __IBASERENDERWINDOW_H__

#include "point.h"
#include "color.h"

namespace sr {

class IBaseRenderWindow {
public:
    IBaseRenderWindow() = default;
    IBaseRenderWindow(const wchar_t *title, int width, int height);
    virtual void show() = 0;
    virtual void clear(const Color &color) = 0;
    virtual int getWidth() const = 0;
    virtual int getHeight() const = 0;
    virtual void setPixel(const Point &point, const Color &color) = 0;
    virtual Color getPixel(const Point &point) const = 0;
};

} // namespace sr

#endif // #ifndef __IBASERENDERWINDOW_H__

