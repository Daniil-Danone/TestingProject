cmake_minimum_required(VERSION 3.10)
project(individual_task_1)

set(CMAKE_CXX_STANDARD 17)

# Вариант 10: Средняя длина идентификатора
add_executable(variant10_analyzer
    variant10/identifier_analyzer.cpp
    variant10/tester_variant10.cpp
)

# Вариант 11: Производная многочлена
add_executable(variant11_derivative
    variant11/polynomial_derivative.cpp
    variant11/tester_variant11.cpp
)

# Генератор тестовых данных
add_executable(test_generator
    shared/generate_test_files.cpp
    variant10/identifier_analyzer.cpp
    variant11/polynomial_derivative.cpp
)