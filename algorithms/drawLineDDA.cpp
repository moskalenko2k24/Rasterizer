#include "../renderwindow.h"
#include "../utils.h"


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

    bool should_swap = abs(y1 - y0) > abs(x1 - x0);
    if (should_swap) {
        swap(x0, y0);
        swap(x1, y1);
    }

    float delta = 1.0 * (y1 - y0) / (x1 - x0);
    float y = y0;
    int step = (x1 < x0) ? -1 : 1;

    for (int x = x0; x != x1 + step; x += step) {
        if (should_swap) {
            setPixel({round(y), x}, color);
        }
        else {
            setPixel({x, round(y)}, color);
        }
        y += step * delta;
    }
}

}
