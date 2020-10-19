// Киреев А.К. 206
#pragma once
#include <utility>
#include <iostream>
#include <cmath>
#define _USE_MATH_DEFINES
#define EPSILON 0.01

template <class T>
struct Triangle {
    using type = T;
    using vertex = std::pair<T, T>;
    vertex center;
    vertex v;
    std::vector<vertex> path;
    bool valid;
    Triangle();
    Triangle(vertex center, vertex v);
    Triangle(std::istream& is);
    ~Triangle() = default;
};

template <class T>
Triangle<T>::Triangle(): center(), v(), valid(false) {}

template <class T>
Triangle<T>::Triangle(vertex center, vertex v): center(center), v(v) {
    valid = true;
    validCheck(*this);
}

template <class T>
Triangle<T>:: Triangle(std::istream& in) {
    T center_X, center_Y, v_X, v_Y;
    in >> center_X >> center_Y >> v_X >> v_Y;
    center = std::make_pair(center_X, center_Y);
    v = std::make_pair(v_X, v_Y);
    // valid check
    valid = true;
    validCheck(*this);
}

template <class T>
void validCheck(Triangle<T>& f) {
    double r = sqrt((f.v.first - f.center.first) * (f.v.first - f.center.first) +
    (f.v.second - f.center.second) * (f.v.second - f.center.second));
    double lenX = f.v.first - f.center.first;
    double lenY = f.v.second - f.center.second;
    double phi = acos(lenX / r);
    if (lenX < 0) {
        if (lenY < 0)
            phi = -M_PI + phi;
    } else {
        if (lenY < 0)
            phi = -phi;
    } 
    for (int i = 0; i < 3; ++i) {
        double angle = 2.0 * M_PI * i / 3.0;
        double next_X = r * cos(angle + phi) + f.center.first;
        double next_Y = r * sin(angle + phi) + f.center.second;
        if (next_X - static_cast<T>(next_X) > EPSILON || next_Y - static_cast<T>(next_Y) > EPSILON) {
            f.valid = false;
        }
        f.path.push_back(std::make_pair(static_cast<T>(next_X), static_cast<T>(next_Y)));
    } 
}
