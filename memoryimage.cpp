#include "memoryimage.h"
#include "loger.h"
#include <cstdlib>
#include <cassert>

namespace sr {



int MemoryImage::getWidth() const {
    return width;
}

int MemoryImage::getHeight() const {
    return height;
}

void MemoryImage::setPixel(int x, int y, const Color &color) {
    //DEBUG_LOG(x);
    //DEBUG_LOG(y);
    if (!(0 <= x && x < width)) {
        DEBUG_LOG(x);
        DEBUG_LOG(y);
    }
    if (!(0 <= y && y < height)) {
        DEBUG_LOG(x);
        DEBUG_LOG(y);
    }
    assert(0 <= x && x < width);
    assert(0 <= y && y < height);
    auto c = RGB(color.B, color.G, color.R);
    buffer[y * width + x] = c;
}

Color MemoryImage::getPixel(int x, int y) const {
    assert(0 <= x && x < width);
    assert(0 <= y && y < height);
    auto c = buffer[y * width + x];
    auto r = GetRValue(c);
    auto g = GetGValue(c);
    auto b = GetBValue(c);
    return Color(r, g, b);
}

void MemoryImage::clear(const Color &color) {
    for (int x = 0; x < width; x++)
        for (int y = 0; y < height; y++)
            setPixel(x, y, color);
}

MemoryImage::MemoryImage(int width, int height):
    width(width), height(height),
    buffer((COLORREF*)calloc(width * height, sizeof(COLORREF)))
    {
        clear(Color::White());
    }

MemoryImage::MemoryImage(MemoryImage &&img) {
    width = img.width;
    height = img.height;
    buffer = img.buffer;
    img.buffer = nullptr;
}

MemoryImage::~MemoryImage() {
    free(buffer);
}



} // namespace sr
