#pragma once

#ifndef __COLOR_H__
#define __COLOR_H__

namespace sr {


struct Color {
    int r, g, b;
    Color();
    Color(int r, int g, int b);

    bool operator == (const Color& rhs) const;
    bool operator != (const Color& rhs) const;

    static Color RGB(int r, int g, int b);

    static const Color& White();
    static const Color& Black();
    static const Color& Red();
    static const Color& Green();
    static const Color& Blue();
    static const Color& Yellow();
    static const Color& Magenta();
    static const Color& Cyan();
};


}

#endif
