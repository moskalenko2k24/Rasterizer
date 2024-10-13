#include "renderwindow.h"
#include "loger.h"
#include <cmath> // round
#include <stack>

namespace sr {



void RenderWindow::drawLineDDA(const Point &a, const Point &b, const Color &color) {
    int x0 = a.x;
    int y0 = a.y;
    int x1 = b.x;
    int y1 = b.y;

    if (x0 == x1 && y0 == y1) {
        setPixel({x0, y0}, color);
        return;
    }

    bool swap = abs(y1 - y0) > abs(x1 - x0);
    if (swap) {
        std::swap(x0, y0);
        std::swap(x1, y1);
    }

    float delta = 1.0 * (y1 - y0) / (x1 - x0);
    float y = y0;
    int step = (x1 < x0) ? -1 : 1;

    for (int x = x0; x != x1 + step; x += step) {
        if (swap) {
            setPixel({(int)round(y), x}, color);
        }
        else {
            setPixel({x, (int)round(y)}, color);
        }
        y += step * delta;
    }
}

void RenderWindow::drawLine(const Point &a, const Point &b, const Color &color) {
    int x0 = a.x;
    int y0 = a.y;
    int x1 = b.x;
    int y1 = b.y;

    if (x0 > x1) {
        std::swap(x0, x1); 
        std::swap(y0, y1);
    }
    
    int dx = x1 - x0;
    int dy = y1 - y0;

    bool drawUp = dy < 0;
    if (drawUp) {
        dy *= -1;
        y1 = y0 + dy;
    }

    bool swap = dy > dx;
    if (swap) {
        std::swap(x0, y0);
        std::swap(x1, y1);
        std::swap(dx, dy);
    }
    int error = 0;
    int y = y0;

    for (int x = x0; x <= x1; x++) {
        int cx = x;
        int cy = y;
        
        if (swap)
            std::swap(cx, cy);

        if (drawUp) {
            int cy0 = swap ? x0 : y0;
            cy = 2 * cy0 - cy;
        }

        setPixel({cx, cy}, color);
        error += dy;
        if (2 * error >= dx)
            y++, error -= dx;
    }
}

void RenderWindow::floodFill(const Point &point, const Color &color) {
    auto current = getPixel({point.x, point.y});
    std::stack<Point> s;
    s.push(point);
    while (!s.empty()) {
        int x = s.top().x;
        int y = s.top().y;
        s.pop();
        if (x < 0 || x >= getWidth() || 
            y < 0 || y >= getHeight())
            continue;
        if (getPixel({x, y}) != current)
            continue;
        setPixel({x, y}, color);
        s.push({x+1, y});
        s.push({x-1, y});
        s.push({x, y+1});
        s.push({x, y-1});
    }
}

void RenderWindow::drawTriangleNaive(const Point &a, const Point &b, const Point &c, const Color &color) {
    int x0 = a.x;
    int y0 = a.y;
    int x1 = b.x;
    int y1 = b.y;
    int x2 = c.x;
    int y2 = c.y;

    if (y0 > y1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }
    if (y1 > y2) {
        std::swap(x1, x2);
        std::swap(y1, y2);
    }
    if (y0 > y1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }

    drawLine({x0, y0}, {x1, y1}, color);
    drawLine({x1, y1}, {x2, y2}, color);
    drawLine({x0, y0}, {x2, y2}, color);
    //floodFill({x0, y0 + 1}, color);
}

void RenderWindow::drawTriangle(const Point &a, const Point &b, const Point &c, const Color &color) {
    int x0 = a.x;
    int y0 = a.y;
    int x1 = b.x;
    int y1 = b.y;
    int x2 = c.x;
    int y2 = c.y;

    if (y0 > y1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }
    if (y1 > y2) {
        std::swap(x1, x2);
        std::swap(y1, y2);
    }
    if (y0 > y1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
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
            std::swap(s, f);
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

} // namespace sr
