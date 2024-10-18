#include "utils.h"

int abs(int x) {
    return x > 0 ? x : -x;
}

int round(double x) {
    return static_cast<int>(x + 0.5);
}
