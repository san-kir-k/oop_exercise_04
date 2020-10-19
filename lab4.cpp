// Киреев А.К. 206
#include <iostream>
#include <utility>
#include <tuple>
#include <sstream>
#include <string>

#include "octagon.hpp"
#include "square.hpp"
#include "triangle.hpp"
#include "handle.hpp"

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

void mainLoop() {
    int command = 0;
    std::string s;
    // создаем tuple из шести фигур (каждая фигура типа int и double)
    std::tuple<Triangle<int>, Square<int>, Octagon<int>, Triangle<double>, Square<double>, Octagon<double> > t =
    {Triangle<int>({0, 0}, {0, 1}), Square<int>({0, 0}, {2, 2}), Octagon<int>({0, 0}, {0, 1}),
    Triangle<double>({0.0, 0.0}, {0.0, 1.0}),  Square<double>({0.0, 0.0}, {2.0, 2.0}), Octagon<double>({0.0, 0.0}, {0.0, 1.0})};
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
                printTuple(t);
                std::cout << "==============================TUPLE_END==============================\n";
                break;
            case 2:
                std::cout << "Total tuple area is: " << getTotalArea(t) << std::endl;
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
