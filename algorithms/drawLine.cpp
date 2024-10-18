#include "../renderwindow.h"
#include "../utils.h"

namespace sr {

void RenderWindow::drawLine(const Point &a, const Point &b, const Color &color) {
    int x0 = a.x;
    int y0 = a.y;
    int x1 = b.x;
    int y1 = b.y;

    if (x0 > x1) {
        swap(x0, x1);
        swap(y0, y1);
    }

    int dx = x1 - x0;
    int dy = y1 - y0;

    bool drawUp = dy < 0;
    if (drawUp) {
        dy *= -1;
        y1 = y0 + dy;
    }

    bool should_swap = dy > dx;
    if (should_swap) {
        swap(x0, y0);
        swap(x1, y1);
        swap(dx, dy);
    }
    int error = 0;
    int y = y0;

    for (int x = x0; x <= x1; x++) {
        int cx = x;
        int cy = y;

        if (should_swap)
            swap(cx, cy);

        if (drawUp) {
            int cy0 = should_swap ? x0 : y0;
            cy = 2 * cy0 - cy;
        }

        setPixel({cx, cy}, color);
        error += dy;
        if (2 * error >= dx)
            y++, error -= dx;
    }
}

}
