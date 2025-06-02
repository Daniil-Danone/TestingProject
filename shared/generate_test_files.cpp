#include <iostream>
#include <string>
#include "../variant10/identifier_analyzer.h"
#include "../variant11/polynomial_derivative.h"
#include <windows.h>


int main() {
    SetConsoleOutputCP(CP_UTF8);
    std::cout << "Генератор тестовых данных\n";
    std::cout << "1. Сгенерировать файл с идентификаторами (вариант 10)\n";
    std::cout << "2. Сгенерировать файл с коэффициентами многочлена (вариант 11)\n";
    std::cout << "Выберите действие: ";

    int choice;
    std::cin >> choice;

    std::string file_path;
    std::cout << "Введите путь для сохранения файла: ";
    std::cin >> file_path;

    if (choice == 1) {
        int total_identifiers, max_length;
        std::cout << "Введите количество идентификаторов: ";
        std::cin >> total_identifiers;
        std::cout << "Введите максимальную длину идентификатора: ";
        std::cin >> max_length;

        if (generate_identifier_test_file(file_path, total_identifiers, max_length)) {
            std::cout << "Файл успешно создан!\n";
        } else {
            std::cerr << "Ошибка при создании файла!\n";
        }
    } else if (choice == 2) {
        int degree;
        double min_coeff, max_coeff;
        std::cout << "Введите степень многочлена: ";
        std::cin >> degree;
        std::cout << "Введите минимальный коэффициент: ";
        std::cin >> min_coeff;
        std::cout << "Введите максимальный коэффициент: ";
        std::cin >> max_coeff;

        if (generate_polynomial_test_file(file_path, degree, min_coeff, max_coeff)) {
            std::cout << "Файл успешно создан!\n";
        } else {
            std::cerr << "Ошибка при создании файла!\n";
        }
    } else {
        std::cerr << "Неверный выбор!\n";
    }

    return 0;
}