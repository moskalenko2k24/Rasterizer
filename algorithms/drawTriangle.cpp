#include "../renderwindow.h"
#include "../utils.h"
#include <utility>

namespace sr {
void RenderWindow::drawTriangle(const Point &a, const Point &b, const Point &c, const Color &color) {
    int x0 = a.x;
    int y0 = a.y;
    int x1 = b.x;
    int y1 = b.y;
    int x2 = c.x;
    int y2 = c.y;

    if (y0 > y1) {
        swap(x0, x1);
        swap(y0, y1);
    }
    if (y1 > y2) {
        swap(x1, x2);
        swap(y1, y2);
    }
    if (y0 > y1) {
        swap(x0, x1);
        swap(y0, y1);
    }
    // (x - x0) / dx = (y - y0) / dy
    // y = y0 + dy / dx * (x - x0)
    // x = x0 + dx / dy * (y - y0)
    auto getX = [](const Point &p1, const Point &p2, int y) {
        if (p1.x == p2.x)
            return p1.x;
        int dy = p2.y - p1.y;
        int dx = p2.x - p1.x;
        return int(p1.x + 1.0f * dx / dy * (y - p1.y));
    };

    std::pair<Point, Point> leftLine{{x0, y0}, {x1, y1}};
    std::pair<Point, Point> rightLine{{x0, y0}, {x2, y2}};
    if (y0 == y1)
        leftLine = {{x1, y1}, {x2, y2}};
    DEBUG_LOG(x0); DEBUG_LOG(y0);
    DEBUG_LOG(x1); DEBUG_LOG(y1);
    DEBUG_LOG(x2); DEBUG_LOG(y2);
    for (int y = y0; y <= y2; y++) {
        //DEBUG_LOG(y);
        int s = getX(leftLine.first, leftLine.second, y);
        int f = getX(rightLine.first, rightLine.second, y);
        if (f < s) {
            swap(s, f);
        }
        for (int x = s; x <= f; x++) {
            //DEBUG_LOG(x);
            //DEBUG_LOG(y);
            setPixel({x, y}, color);
        }
        if (y == y1) {
            leftLine = {{s, y}, {x2, y2}};
            rightLine = {{f, y}, {x2, y2}};
        }
    }

}

}
