#include <iostream>
#include <string>
#include "identifier_analyzer.h"
#include <windows.h>


int main() {
    SetConsoleOutputCP(CP_UTF8);
    std::string file_path;
    std::cout << "Введите путь к файлу с идентификаторами: ";
    std::cin >> file_path;

    double average_length;
    int result = calculate_average_identifier_length(file_path, &average_length);

    if (result == 0) {
        std::cout << "Средняя длина идентификатора: " << average_length << std::endl;
    } else if (result == -1) {
        std::cerr << "Ошибка: файл не открыт!" << std::endl;
    } else {
        std::cerr << "Ошибка: в файле нет идентификаторов!" << std::endl;
    }

    return 0;
}