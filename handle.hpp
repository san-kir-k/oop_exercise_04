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

//
// шаблонная мета-функция func структуры Print для вывода фигуры на экран. 
//
struct Print {
    template<class Figure>
    void func(Figure& f) {    
        using Type = typename Figure::type;  
        // проверка фигуры на валидность (она может не существовать в каких-то координатах)
        if (!f.valid) {
            if (std::is_same<Figure, Triangle<Type>>::value) {
                std::cout << "Invalid figure: Triangle<" << typeid(Type).name() << ">" << std::endl;
            } else if (std::is_same<Figure, Square<Type>>::value) {
                std::cout << "Invalid figure: Square<" << typeid(Type).name() << ">" << std::endl;
            } else {
                std::cout << "Invalid figure: Octagon<" << typeid(Type).name() << ">" << std::endl;
            }
            return;
        }  // конец проверки
        // вывод координат вершин фигуры
        std::cout.precision(3);
        std::cout << "[ ";
        if (std::is_same<Figure, Triangle<Type>>::value) { // при помощи шаблона is_same проверяем, что за фигуру мы обрабатываем
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
        std::cout << "]" << std::endl; // конец вывода координат вершин фигуры
    }
};

//
// шаблонная мета-функция func структуры Area для подсчета общей площади фигур в tuple 
// результат записывается в поле объекта структуры Area
//
struct Area {
    double res;
    template <class Figure>
    void func(Figure& f) {
        using Type = typename Figure::type;
        // проверка фигуры на валидность
        if (!f.valid) {
            if (std::is_same<Figure, Triangle<Type>>::value) {
                std::cout << "Invalid figure: Triangle<" << typeid(Type).name() << ">" << std::endl;
            } else if (std::is_same<Figure, Square<Type>>::value) {
                std::cout << "Invalid figure: Square<" << typeid(Type).name() << ">" << std::endl;
            } else {
                std::cout << "Invalid figure: Octagon<" << typeid(Type).name() << ">" << std::endl;
            }
            return;
        } // конец проверки фигуры на валидность
        double r = sqrt((f.v.first - f.center.first) * (f.v.first - f.center.first) +
        (f.v.second - f.center.second) * (f.v.second - f.center.second));
        // для каждого типа фигуры считаем плозадь по-своему, отделяя типы при помощи шаблона is_same
        if (std::is_same<Figure, Triangle<Type>>::value) {
            res += 3.0 * sqrt(3.0) * r * r / 4.0;
        } else if (std::is_same<Figure, Square<Type>>::value) {
            res += 2.0 * r * r;
        } else {
            res += 2.0 * sqrt(2.0) * r * r;
        }
    }
};

//
// шаблонная мета-функция для применения функции/метода callback к элементу кортежа t по индексу Index
//
template<int Index, class Callback, class... Args>
struct IterateTuple {
    static void next(std::tuple<Args...>& t, Callback& callback) {
        IterateTuple<Index - 1, Callback, Args...>::next(t, callback); // запускаем функцию рекурсивно для Index - 1
        callback.func(std::get<Index>(t)); // применяем callback
    }
};

//
// краевой случай (Index = 0) шаблонной мета-функции для применения функции/метода callback к элементу кортежа t по индексу Index
// 
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
    // callback = Print print
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
    // callback = Area area, результат в переменной res объекта area
    IterateTuple<size - 1, Area, Args...>::next(t, area);
    return area.res;
}
