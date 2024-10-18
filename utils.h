#pragma once

#include <iostream>

#define DEBUG_LOG(x) std::cout << "In " << __PRETTY_FUNCTION__  << " " << #x << " = " << x << '\n'

int abs(int x);
int round(double x);

template <typename T>
void swap(T &a, T &b) {
    T t = a;
    a = b;
    b = t;
}
