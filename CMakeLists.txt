cmake_minimum_required(VERSION 3.10)
project(TestingProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Общие файлы
set(SHARED_SOURCES
    shared/test_runner.cpp
)

# Вариант 10
add_executable(variant10
    variant10/tester_variant10.cpp
    variant10/identifier_analyzer.cpp
    ${SHARED_SOURCES}
)

# Вариант 11
add_executable(variant11
    variant11/tester_variant11.cpp
    variant11/polynomial_derivative.cpp
    ${SHARED_SOURCES}
)

# Установка кодировки для Windows
if(WIN32)
    target_compile_options(variant10 PRIVATE /utf-8)
    target_compile_options(variant11 PRIVATE /utf-8)
endif()