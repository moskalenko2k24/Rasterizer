#include "../renderwindow.h"
#include "../utils.h"
#include <utility>

namespace sr {

void RenderWindow::drawTriangleNaive(const Point &a, const Point &b, const Point &c, const Color &color) {
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

    drawLine({x0, y0}, {x1, y1}, color);
    drawLine({x1, y1}, {x2, y2}, color);
    drawLine({x0, y0}, {x2, y2}, color);
    //floodFill({x0, y0 + 1}, color);
}

} // namespace sr
