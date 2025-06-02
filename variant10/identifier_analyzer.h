#pragma once
#include <string>
#include <fstream>

/**
 * @brief Вычисляет среднюю длину идентификаторов в файле.
 * @param file_path Путь к файлу с последовательностью символов.
 * @param average_length Указатель для сохранения средней длины.
 * @return Код ошибки:
 *   0 — успех,
 *  -1 — файл не открыт,
 *  -2 — нет идентификаторов.
 */
int calculate_average_identifier_length(const std::string& file_path, double* average_length);

/**
 * @brief Генерирует тестовый файл с идентификаторами.
 * @param output_path Путь для сохранения файла.
 * @param total_identifiers Количество идентификаторов.
 * @param max_length Максимальная длина идентификатора.
 * @return true, если файл создан успешно.
 */
bool generate_identifier_test_file(const std::string& output_path, int total_identifiers, int max_length);