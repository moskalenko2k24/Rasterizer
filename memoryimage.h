#pragma once

#ifndef __MEMORYIMAGE_H__
#define __MEMORYIMAGE_H__

#include "color.h"
#include <windows.h>

namespace sr {



class MemoryImage {
private:
    int width, height;
    COLORREF *buffer;
public:
    int getWidth() const;
    int getHeight() const;
    void setPixel(int x, int y, const Color &color);
    Color getPixel(int x, int y) const;
    void clear(const Color &color);
    MemoryImage(int width, int height);
    MemoryImage(const MemoryImage &img) = delete;
    MemoryImage(MemoryImage &&img);
    ~MemoryImage();
    friend class BaseRenderWindow;
};



} // namespace sr

#endif // #ifndef __MEMORYIMAGE_H__
