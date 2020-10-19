// Киреев А.К. 206
#include <iostream>
#include <tuple>
#include <utility>
#include <cmath>
#include <string>
#include <typeinfo>
#define _USE_MATH_DEFINES

#include "octagon.hpp"
#include "square.hpp"
#include "triangle.hpp"

struct Print {
    template<class Figure>
    void func(Figure& f) {    
        using Type = typename Figure::type;  
        if (!f.valid) {
            if (std::is_same<Figure, Triangle<Type>>::value) {
                std::cout << "Invalid figure: Triangle<" << typeid(Type).name() << ">" << std::endl;
            } else if (std::is_same<Figure, Square<Type>>::value) {
                std::cout << "Invalid figure: Square<" << typeid(Type).name() << ">" << std::endl;
            } else {
                std::cout << "Invalid figure: Octagon<" << typeid(Type).name() << ">" << std::endl;
            }
            return;
        } 
        std::cout.precision(3);
        std::cout << "[ ";
        if (std::is_same<Figure, Triangle<Type>>::value) {
            for (int i = 0; i < 3; ++i) {
                std::cout << "("  << std::fixed << f.path[i].first << ", " << std::fixed << f.path[i].second << ") ";
            }  
        } else if (std::is_same<Figure, Square<Type>>::value) {
            for (int i = 0; i < 4; ++i) {
                std::cout << "("  << std::fixed << f.path[i].first << ", " << std::fixed << f.path[i].second << ") ";
            }
        } else {
            for (int i = 0; i < 8; ++i) {
                std::cout << "("  << std::fixed << f.path[i].first << ", " << std::fixed << f.path[i].second << ") ";
            }
        }
        std::cout << "]" << std::endl;
    }
};

struct Area {
    double res;
    template <class Figure>
    void func(Figure& f) {
        using Type = typename Figure::type;
        if (!f.valid) {
            if (std::is_same<Figure, Triangle<Type>>::value) {
                std::cout << "Invalid figure: Triangle<" << typeid(Type).name() << ">" << std::endl;
            } else if (std::is_same<Figure, Square<Type>>::value) {
                std::cout << "Invalid figure: Square<" << typeid(Type).name() << ">" << std::endl;
            } else {
                std::cout << "Invalid figure: Octagon<" << typeid(Type).name() << ">" << std::endl;
            }
            return;
        } 
        double r = sqrt((f.v.first - f.center.first) * (f.v.first - f.center.first) +
        (f.v.second - f.center.second) * (f.v.second - f.center.second));
        if (std::is_same<Figure, Triangle<Type>>::value) {
            res += 3.0 * sqrt(3.0) * r * r / 4.0;
        } else if (std::is_same<Figure, Square<Type>>::value) {
            res += 2.0 * r * r;
        } else {
            res += 2.0 * sqrt(2.0) * r * r;
        }
    }
};

template<int Index, class Callback, class... Args>
struct IterateTuple {
    static void next(std::tuple<Args...>& t, Callback& callback) {
        IterateTuple<Index - 1, Callback, Args...>::next(t, callback);
        callback.func(std::get<Index>(t));
    }
};

template<class Callback, class... Args>
struct IterateTuple<0, Callback, Args...> {
    static void next(std::tuple<Args...>& t, Callback& callback) {
        callback.func(std::get<0>(t));
    }
};

template<class... Args>
void printTuple(std::tuple<Args...>& t) {
    Print print;
    const size_t size = std::tuple_size<std::tuple<Args...>>::value;
    if (size == 0) {
        return;
    }
    IterateTuple<size - 1, Print, Args...>::next(t, print);
}

template<class... Args>
double getTotalArea(std::tuple<Args...>& t) {
    Area area;
    area.res = 0.0;
    const size_t size = std::tuple_size<std::tuple<Args...>>::value;
    if (size == 0) {
        return 0.0;
    }
    IterateTuple<size - 1, Area, Args...>::next(t, area);
    return area.res;
}
