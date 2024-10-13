#include "color.h"

namespace sr {



Color::Color(): R(0), G(0), B(0) {}

Color::Color(int r, int g, int b): R(r), G(g), B(b) {}

bool Color::operator == (const Color& rhs) const {
    return R == rhs.R && 
           G == rhs.G && 
           B == rhs.B;
}

bool Color::operator != (const Color& rhs) const {
    return !(*this == rhs);
}

Color Color::RGB(int r, int g, int b) {
    return Color(r, g, b);
}

const Color& Color::White() {
    static const auto value = Color(255, 255, 255);
    return value;
}

const Color& Color::Black() {
    static const auto value = Color(0, 0, 0);
    return value;
}

const Color& Color::Red() {
    static const auto value = Color(255, 0, 0);
    return value;
}

const Color& Color::Green() {
    static const auto value = Color(0, 255, 0);
    return value;
}

const Color& Color::Blue() {
    static const auto value = Color(0, 0, 255);
    return value;
}

const Color& Color::Yellow() {
    static const auto value = Color(255, 255, 0);
    return value;
}

const Color& Color::Magenta() {
    static const auto value = Color(255, 0, 255);
    return value;
}

const Color& Color::Cyan() {
    static const auto value = Color(0, 255, 255);
    return value;
}



} // namespace sr