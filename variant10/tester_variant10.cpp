#include <iostream>
#include <string>
#include <filesystem>
#include <windows.h>
#include "identifier_analyzer.h"
#include "../shared/test_runner.h"

namespace fs = std::filesystem;

bool test_empty_file() {
    const std::string test_file = "test_empty.txt";
    std::ofstream f(test_file);
    f.close();
    
    double result;
    int code = calculate_average_identifier_length(test_file, &result);
    fs::remove(test_file);
    return code == -2;
}

bool test_nonexistent_file() {
    double result;
    return calculate_average_identifier_length("nonexistent.txt", &result) == -1;
}

bool test_single_identifier() {
    const std::string test_file = "test_single.txt";
    std::ofstream f(test_file);
    f << "test123";
    f.close();
    
    double result;
    int code = calculate_average_identifier_length(test_file, &result);
    fs::remove(test_file);
    return code == 0 && result == 7.0;
}

bool test_multiple_identifiers() {
    const std::string test_file = "test_multiple.txt";
    std::ofstream f(test_file);
    f << "test123 abc def456";
    f.close();
    
    double result;
    int code = calculate_average_identifier_length(test_file, &result);
    fs::remove(test_file);
    return code == 0 && std::abs(result - 5.333333) < 1e-6;
}

bool test_generator() {
    const std::string test_file = "test_generated.txt";
    bool success = generate_identifier_test_file(test_file, 10, 5);
    if (!success) return false;
    
    double result;
    int code = calculate_average_identifier_length(test_file, &result);
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
        runner.run_test("Тест одного идентификатора", test_single_identifier);
        runner.run_test("Тест нескольких идентификаторов", test_multiple_identifiers);
        
        // Тесты с генератором
        runner.run_test_with_time("Тест генератора", test_generator);
        
        // Интерактивное тестирование
        std::string input_file;
        std::cout << "Введите путь к файлу для тестирования: ";
        std::getline(std::cin, input_file);
        
        double result;
        int code = calculate_average_identifier_length(input_file, &result);
        
        runner.run_test("Интерактивный тест", [&]() {
            if (code == 0) {
                std::cout << "Средняя длина идентификатора: " << result << std::endl;
                return true;
            } else {
                std::cerr << "Ошибка: " << (code == -1 ? "файл не открыт" : "нет идентификаторов") << std::endl;
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