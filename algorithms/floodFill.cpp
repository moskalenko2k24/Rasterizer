#include "../renderwindow.h"
#include "../utils.h"
#include <stack>

namespace sr {

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

}
