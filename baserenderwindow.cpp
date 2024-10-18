#include "baserenderwindow.h"
#include "utils.h"
#include <cassert>

namespace sr {

    int MemoryImage::getWidth() const {
        return width;
    }

    int MemoryImage::getHeight() const {
        return height;
    }

    void MemoryImage::setPixel(int x, int y, const Color &color) {
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
        COLORREF c = RGB(color.b, color.g, color.r);
        buffer[y * width + x] = c;
    }

    Color MemoryImage::getPixel(int x, int y) const {
        assert(0 <= x && x < width);
        assert(0 <= y && y < height);
        COLORREF c = buffer[y * width + x];
        int r = static_cast<int>(GetRValue(c));
        int g = static_cast<int>(GetGValue(c));
        int b = static_cast<int>(GetBValue(c));
        return Color(r, g, b);
    }

    void MemoryImage::clear(const Color &color) {
        for (int x = 0; x < width; x++)
            for (int y = 0; y < height; y++)
                setPixel(x, y, color);
    }

    MemoryImage::MemoryImage(int width, int height):
        width(width), height(height),
        buffer(static_cast<COLORREF*>(
            calloc(width * height, sizeof(COLORREF))
        ))
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


LRESULT CALLBACK BaseRenderWindow::WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_NCCREATE:
        {
            CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
            auto pThis = (MemoryImage*)pCreate->lpCreateParams;
            SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pThis);
            break;
        }
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        case WM_PAINT:
        {
            auto img = reinterpret_cast<MemoryImage*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
            int width = img->getWidth();
            int height = img->getHeight();
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            HBITMAP map = CreateBitmap(width, height, 1, 8 * 4, (void*)(img->buffer));
            HDC src = CreateCompatibleDC(hdc);
            SelectObject(src, map);
            BitBlt(hdc, 0, 0, width, height, src, 0, 0, SRCCOPY);
            DeleteDC(src);
            EndPaint(hwnd, &ps);
            break;
        }
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

const wchar_t* BaseRenderWindow::ClassName() {
    static const auto value = L"Software Render by @moskalenco_a";
    return value;
}

void BaseRenderWindow::Register() {
    WNDCLASS wc = {};

    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc   = WndProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = ClassName();
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.cbWndExtra = sizeof(MemoryImage*);
    RegisterClass(&wc);
}

void BaseRenderWindow::Create() {
    RECT rect;
    rect.top = rect.left = 0;
    rect.bottom = img.getHeight();
    rect.right = img.getWidth();
    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
    auto width = rect.right - rect.left;
    auto height = rect.bottom - rect.top;
    hwnd = CreateWindowEx(
        0,                       // Optional window styles
        ClassName(),             // Window class
        title,                   // Window text
        WS_OVERLAPPEDWINDOW,     // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, width, height,

        NULL,       // Parent window
        NULL,       // Menu
        hInstance,  // Instance handle
        &img        // Additional application data
    );

    // if (hwnd == NULL) {} // ???
}

void BaseRenderWindow::Show() {
    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);
    // Run the message loop
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

BaseRenderWindow::BaseRenderWindow(const wchar_t *title, int width, int height):
    img(width, height), title(title), hInstance(GetModuleHandle(nullptr)) {}

void BaseRenderWindow::show() {
    Register();
    Create();
    Show();
}

void BaseRenderWindow::clear(const Color &color) {
    img.clear(color);
}

int BaseRenderWindow::getWidth() const {
    return img.getWidth();
}

int BaseRenderWindow::getHeight() const {
    return img.getHeight();
}

void BaseRenderWindow::setPixel(const Point &point, const Color &color) {
    img.setPixel(point.x, point.y, color);
}

Color BaseRenderWindow::getPixel(const Point &point) const {
    return img.getPixel(point.x, point.y);
}



} // namespace sr
