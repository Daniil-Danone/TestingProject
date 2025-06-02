#pragma once
#include <vector>
#include <string>

/**
 * @brief Вычисляет значение производной многочлена в точке.
 * @param file_path Путь к файлу с коэффициентами (по убыванию степеней).
 * @param x Точка, в которой вычисляется производная.
 * @param derivative Указатель для сохранения результата.
 * @return Код ошибки:
 *   0 — успех,
 *  -1 — файл не открыт,
 *  -2 — файл пуст.
 */
int calculate_polynomial_derivative(const std::string& file_path, double x, double* derivative);

/**
 * @brief Генерирует тестовый файл с коэффициентами многочлена.
 * @param output_path Путь для сохранения файла.
 * @param degree Степень многочлена.
 * @param min_coeff Минимальное значение коэффициента.
 * @param max_coeff Максимальное значение коэффициента.
 * @return true, если файл создан успешно.
 */
bool generate_polynomial_test_file(const std::string& output_path, int degree, double min_coeff, double max_coeff);