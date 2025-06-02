#include "test_runner.h"
#include <iostream>
#include <ctime>

TestRunner::TestRunner(const std::string& output_file, bool append) 
    : output_file_(output_file) {
    std::ios_base::openmode mode = std::ios::out;
    if (append) {
        mode |= std::ios::app;
    }
    out_.open(output_file, mode);
    
    if (!out_.is_open()) {
        throw std::runtime_error("Не удалось открыть файл для записи результатов");
    }

    // Записываем заголовок с датой и временем
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    out_ << "=== Результаты тестирования от " << std::ctime(&time) << "===\n\n";
}

TestRunner::~TestRunner() {
    if (out_.is_open()) {
        out_.close();
    }
}

void TestRunner::run_test(const std::string& name, std::function<bool()> test_func) {
    TestResult result;
    result.test_name = name;
    result.success = test_func();
    result.execution_time = 0.0;
    results_.push_back(result);
}

void TestRunner::run_test_with_time(const std::string& name, std::function<bool()> test_func) {
    TestResult result;
    result.test_name = name;
    
    auto start = std::chrono::high_resolution_clock::now();
    result.success = test_func();
    auto end = std::chrono::high_resolution_clock::now();
    
    result.execution_time = std::chrono::duration<double>(end - start).count();
    results_.push_back(result);
}

void TestRunner::write_results() {
    out_ << "Итоги тестирования:\n";
    out_ << "==================\n\n";
    
    int total = results_.size();
    int passed = 0;
    
    for (const auto& result : results_) {
        out_ << "Тест: " << result.test_name << "\n";
        out_ << "Результат: " << (result.success ? "ПРОЙДЕН" : "НЕ ПРОЙДЕН") << "\n";
        if (result.execution_time > 0) {
            out_ << "Время выполнения: " << std::fixed << std::setprecision(6) 
                 << result.execution_time << " сек\n";
        }
        out_ << "-------------------\n";
        
        if (result.success) passed++;
    }
    
    out_ << "\nОбщая статистика:\n";
    out_ << "Всего тестов: " << total << "\n";
    out_ << "Пройдено: " << passed << "\n";
    out_ << "Не пройдено: " << (total - passed) << "\n";
    out_ << "Процент успешных: " << (total > 0 ? (passed * 100.0 / total) : 0) << "%\n";
} 