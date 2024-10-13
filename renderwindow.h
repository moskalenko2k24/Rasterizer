#pragma once

#ifndef __RENDERWINDOW_H__
#define __RENDERWINDOW_H__

#include "baserenderwindow.h"

namespace sr {


class RenderWindow: public BaseRenderWindow {
public:
    using BaseRenderWindow::BaseRenderWindow;    
    void drawLineDDA(const Point &a, const Point &b, const Color &color);
    void drawLine(const Point &a, const Point &b, const Color &color);
    void floodFill(const Point &point, const Color &color);
    void drawTriangleNaive(const Point &a, const Point &b, const Point &c, const Color &color);
    void drawTriangle(const Point &a, const Point &b, const Point &c, const Color &color);
};


}

#endif