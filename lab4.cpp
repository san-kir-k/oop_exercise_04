// Киреев А.К. 206
#include <iostream>
#include <utility>
#include <tuple>
#include <sstream>
#include <string>

#include "octagon.hpp"
#include "square.hpp"
#include "triangle.hpp"
#include "tuple_handler.hpp"

//
// мануал
//
void help() {
    std::cout << "Command -- Description\n" <<
                "1 -- Display figures in tuple\n" <<
                "2 -- Calculate total area of figures in tuple  \n" <<
                "3 -- Display help\n" <<
                "4 -- End program" << std::endl;
}

//
// интерактивный ввод
//
std::tuple<Square<int>, Square<double>, Square<size_t>, Triangle<double>, Triangle<int>, Octagon<double>>
tupleCreat() {
    std::cout << "Enter center and vertex of Square<int>:\n";
    int c1_x, v1_x, c1_y, v1_y;
    if (!(std::cin >> c1_x >> c1_y >> v1_x >> v1_y)) {
        std::cout << "Input error.\n";
    }
    std::cout << "Enter center and vertex of Square<double>:\n";
    int c2_x, v2_x, c2_y, v2_y;
    if (!(std::cin >> c2_x >> c2_y >> v2_x >> v2_y)) {
        std::cout << "Input error.\n";
    }
    std::cout << "Enter center and vertex of Square<size_t>:\n";
    int c3_x, v3_x, c3_y, v3_y;
    if (!(std::cin >> c3_x >> c3_y >> v3_x >> v3_y)) {
        std::cout << "Input error.\n";
    }
    std::cout << "Enter center and vertex of Triangle<double>:\n";
    int c4_x, v4_x, c4_y, v4_y;
    if (!(std::cin >> c4_x >> c4_y >> v4_x >> v4_y)) {
        std::cout << "Input error.\n";
    }
    std::cout << "Enter center and vertex of Triangle<int>:\n";
    int c5_x, v5_x, c5_y, v5_y;
    if (!(std::cin >> c5_x >> c5_y >> v5_x >> v5_y)) {
        std::cout << "Input error.\n";
    }
    std::cout << "Enter center and vertex of Octagon<double>:\n";
    int c6_x, v6_x, c6_y, v6_y;
    if (!(std::cin >> c6_x >> c6_y >> v6_x >> v6_y)) {
        std::cout << "Input error.\n";
    }
    std::tuple<Square<int>, Square<double>, Square<size_t>, Triangle<double>, Triangle<int>, Octagon<double>> t =
    {Square<int>({c1_x, c1_y}, {v1_x, v1_y}), Square<double>({c2_x, c2_y}, {v2_x, v2_y}),
    Square<size_t>({c3_x, c3_y}, {v3_x, v3_y}), Triangle<double>({c4_x, c4_y}, {v4_x, v4_y}),
    Triangle<int>({c5_x, c5_y}, {v5_x, v5_y}), Octagon<double>({c6_x, c6_y}, {v6_x, v6_y})};
    return t;
}

void mainLoop() {
    int command = 0;
    std::string s;
    // создаем tuple из шести фигур разного типа
    std::tuple<Square<int>, Square<double>, Square<size_t>, Triangle<double>, Triangle<int>, Octagon<double>> t = tupleCreat();
    // парсер команд
    while (std::cout << "Cmd: " && std::cin >> s) {
        if (s.length() > 1) {
            std::cout << "Invalid command." << std::endl;
            continue;
        }
        std::stringstream ss(s);
        ss >> command;
        if (command == 4)
            break;
        switch (command) {
            case 1:
                std::cout << "=============================TUPLE_START=============================\n";
                printTuple<decltype(t),0>(t);
                std::cout << "==============================TUPLE_END==============================\n";
                break;
            case 2:
                std::cout << "Total tuple area is: " << getTotalArea<decltype(t),0>(t) << std::endl;
                break;
            case 3:
                help();
                break;
            default:
                std::cout << "Invalid command!" << std::endl; 
                break;
        }
    }
}

int main() {
    help();
    mainLoop();
    return 0;
}
