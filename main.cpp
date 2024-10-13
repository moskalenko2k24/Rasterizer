#include "renderwindow.h"

int main() {
    sr::RenderWindow window(L"Растеризатор by @moskalenko2k24", 800, 800);
    //window.drawTriangle({500, 50}, {100, 300}, {700, 400}, sr::Color::Magenta());
    //int w = window.getWidth();
    //int h = window.getHeight();

    /*auto testLine = [&window](const sr::Point &a, const sr::Point &b) {
        window.drawLineDDA(a, b, sr::Color::Black());
        window.drawLine(a, b, sr::Color::Magenta());
    };*/

    // Testing line drawing
    //testLine({w / 2, h / 2}, {w / 4, 0});
    //testLine({w / 2, h / 2}, {3 * w / 4, 0});
    //testLine({w / 2, h / 2}, {w / 4, h-1});
    //testLine({w / 2, h / 2}, {3 * w / 4, h});
    //testLine({0, h / 2}, {w - 1, h / 2}); // H
    //testLine({w / 2, 0}, {w / 2, h - 1}); // V

    auto testTriangle = [&window](const sr::Point &a, const sr::Point &b, const sr::Point &c) {
        window.drawTriangleNaive(a, b, c, sr::Color::Black());
        window.drawTriangle(a, b, c, sr::Color::Magenta());
        //window.drawTriangleNaive(a, b, c, sr::Color::Magenta());
    };

    //testTriangle({300, 300}, {600, 300}, {300, 600}); // fixed
    //testTriangle({300, 300}, {600, 600}, {300, 600});
    //testTriangle({0, 0}, {799, 799}, {500, 700});
    //testTriangle({300, 300}, {700, 50}, {500, 700});
    testTriangle({500, 50}, {100, 300}, {700, 400});
    window.show();
}
