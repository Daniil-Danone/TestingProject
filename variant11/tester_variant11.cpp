#include <iostream>
#include <string>
#include "polynomial_derivative.h"
#include <windows.h>


int main() {
    SetConsoleOutputCP(CP_UTF8);
    
    std::string file_path;
    double x;
    std::cout << "Введите путь к файлу с коэффициентами: ";
    std::cin >> file_path;
    std::cout << "Введите точку x: ";
    std::cin >> x;

    double derivative;
    int result = calculate_polynomial_derivative(file_path, x, &derivative);

    if (result == 0) {
        std::cout << "Значение производной в точке " << x << ": " << derivative << std::endl;
    } else if (result == -1) {
        std::cerr << "Ошибка: файл не открыт!" << std::endl;
    } else {
        std::cerr << "Ошибка: файл пуст!" << std::endl;
    }

    return 0;
}