#include <iostream>
#include <string>
#include <filesystem>
#include <windows.h>
#include "polynomial_derivative.h"
#include "../shared/test_runner.h"

namespace fs = std::filesystem;

bool test_empty_file() {
    const std::string test_file = "test_empty.txt";
    std::ofstream f(test_file);
    f.close();
    
    double result;
    int code = calculate_polynomial_derivative(test_file, 1.0, &result);
    fs::remove(test_file);
    return code == -2;
}

bool test_nonexistent_file() {
    double result;
    return calculate_polynomial_derivative("nonexistent.txt", 1.0, &result) == -1;
}

bool test_constant_polynomial() {
    const std::string test_file = "test_constant.txt";
    std::ofstream f(test_file);
    f << "5.0";
    f.close();
    
    double result;
    int code = calculate_polynomial_derivative(test_file, 1.0, &result);
    fs::remove(test_file);
    return code == 0 && result == 0.0;
}

bool test_linear_polynomial() {
    const std::string test_file = "test_linear.txt";
    std::ofstream f(test_file);
    f << "2.0 1.0"; // 2x + 1
    f.close();
    
    double result;
    int code = calculate_polynomial_derivative(test_file, 1.0, &result);
    fs::remove(test_file);
    return code == 0 && result == 2.0;
}

bool test_quadratic_polynomial() {
    const std::string test_file = "test_quadratic.txt";
    std::ofstream f(test_file);
    f << "1.0 2.0 1.0"; // x^2 + 2x + 1
    f.close();
    
    double result;
    int code = calculate_polynomial_derivative(test_file, 2.0, &result);
    fs::remove(test_file);
    return code == 0 && result == 6.0; // 2x + 2 at x=2
}

bool test_generator() {
    const std::string test_file = "test_generated.txt";
    bool success = generate_polynomial_test_file(test_file, 3, -10.0, 10.0);
    if (!success) return false;
    
    double result;
    int code = calculate_polynomial_derivative(test_file, 1.0, &result);
    fs::remove(test_file);
    return code == 0;
}

int main(int argc, char* argv[]) {
    SetConsoleOutputCP(CP_UTF8);
    
    std::string output_file;
    bool append = false;
    
    if (argc > 1) {
        output_file = argv[1];
        append = true;
    } else {
        std::cout << "Введите имя файла для результатов тестирования: ";
        std::getline(std::cin, output_file);
    }
    
    try {
        TestRunner runner(output_file, append);
        
        // Базовые тесты
        runner.run_test("Тест пустого файла", test_empty_file);
        runner.run_test("Тест несуществующего файла", test_nonexistent_file);
        runner.run_test("Тест константного многочлена", test_constant_polynomial);
        runner.run_test("Тест линейного многочлена", test_linear_polynomial);
        runner.run_test("Тест квадратичного многочлена", test_quadratic_polynomial);
        
        // Тесты с генератором
        runner.run_test_with_time("Тест генератора", test_generator);
        
        // Интерактивное тестирование
        std::string input_file;
        double x;
        std::cout << "Введите путь к файлу с коэффициентами: ";
        std::getline(std::cin, input_file);
        std::cout << "Введите точку x: ";
        std::cin >> x;
        
        double result;
        int code = calculate_polynomial_derivative(input_file, x, &result);
        
        runner.run_test("Интерактивный тест", [&]() {
            if (code == 0) {
                std::cout << "Значение производной в точке " << x << ": " << result << std::endl;
                return true;
            } else {
                std::cerr << "Ошибка: " << (code == -1 ? "файл не открыт" : "файл пуст") << std::endl;
                return false;
            }
        });
        
        runner.write_results();
        
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}