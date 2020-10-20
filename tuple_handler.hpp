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

template <class T>
double getArea(T& figure) {
    using Type = typename T::type;
    double res = 0.0;
    if (!figure.valid) {
        return 0.0;
    }
    double r = sqrt((figure.v.first - figure.center.first) * (figure.v.first - figure.center.first) +
    (figure.v.second - figure.center.second) * (figure.v.second - figure.center.second));
    if constexpr (std::is_same<decltype(figure), Triangle<Type>&>::value) {
        res += 3.0 * sqrt(3.0) * r * r / 4.0;
    } else if constexpr (std::is_same<decltype(figure), Square<Type>&>::value) {
        res += 2.0 * r * r;
    } else if constexpr (std::is_same<decltype(figure), Octagon<Type>&>::value) {
        res += 2.0 * sqrt(2.0) * r * r;
    } else {
        return 0.0;
    }
    return res;
}

template <class T, int index>
double getTotalArea(T& tuple) {
    auto figure = std::get<index>(tuple);
    double res = getArea(figure);
    if constexpr ((index+1) < std::tuple_size<T>::value) {
        return res + getTotalArea<T, index + 1>(tuple);
    }
    return res;
}

template <class T>
void print(T& figure) {
    using Type = typename T::type;  
    // проверка фигуры на валидность (она может не существовать в каких-то координатах)
    if (!figure.valid) {
        if constexpr (std::is_same<decltype(figure), Triangle<Type>&>::value) {
            std::cout << "Invalid figure: Triangle<" << typeid(Type).name() << ">" << std::endl;
        } else if constexpr (std::is_same<decltype(figure), Square<Type>&>::value) {
            std::cout << "Invalid figure: Square<" << typeid(Type).name() << ">" << std::endl;
        } else if constexpr (std::is_same<decltype(figure), Octagon<Type>&>::value) {
            std::cout << "Invalid figure: Octagon<" << typeid(Type).name() << ">" << std::endl;
        } else {
            std::cout << "Invalid undefined figure." << std::endl;
        }
        return;
    }  // конец проверки
    // вывод координат вершин фигуры
    std::cout.precision(3);
    std::cout << "[ ";
    if constexpr 
    ((std::is_same<decltype(figure), Triangle<Type>&>::value) || 
    (std::is_same<decltype(figure), Square<Type>&>::value) ||
    (std::is_same<decltype(figure), Octagon<Type>&>::value)) { 
        for (int i = 0; i < figure.path.size(); ++i) {
            std::cout << "("  << std::fixed << figure.path[i].first << ", " << std::fixed << figure.path[i].second << ") ";
        }  
    }
    std::cout << "]" << std::endl; // конец вывода координат вершин фигуры
}

template <class T,size_t index> 
typename std::enable_if<index >= std::tuple_size<T>::value, void>::type 
printTuple(T& tuple){
    std::cout << std::endl;
}

template <class T,size_t index>
typename std::enable_if<index < std::tuple_size<T>::value, void>::type 
printTuple(T& tuple){
    auto figure = std::get<index>(tuple);
    print(figure);
    printTuple<T, index + 1>(tuple);
}
