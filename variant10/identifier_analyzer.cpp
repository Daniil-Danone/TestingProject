#include "identifier_analyzer.h"
#include <fstream>
#include <cctype>
#include <random>


int calculate_average_identifier_length(const std::string& file_path, double* average_length) {
    std::ifstream file(file_path);
    if (!file.is_open()) {
        return -1;  // Ошибка открытия файла
    }

    int total_length = 0;
    int count = 0;
    bool in_identifier = false;
    int current_length = 0;
    char c;

    while (file.get(c)) {
        if (isalpha(c) && !in_identifier) {
            in_identifier = true;
            current_length = 1;
        } else if (in_identifier && (isalnum(c))) {
            current_length++;
        } else if (in_identifier) {
            in_identifier = false;
            total_length += current_length;
            count++;
        }
    }

    // Обработка последнего идентификатора в файле
    if (in_identifier) {
        total_length += current_length;
        count++;
    }

    file.close();

    if (count == 0) {
        return -2;  // Нет идентификаторов
    }

    *average_length = static_cast<double>(total_length) / count;
    return 0;
}

bool generate_identifier_test_file(const std::string& output_path, int total_identifiers, int max_length) {
    std::ofstream file(output_path);
    if (!file.is_open()) {
        return false;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> length_dist(1, max_length);
    std::uniform_int_distribution<int> char_dist(0, 61);  // 0-9, A-Z, a-z

    const char charset[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < total_identifiers; ++i) {
        int length = length_dist(gen);
        file << static_cast<char>(charset[10 + char_dist(gen) % 52]);  // Первый символ — буква

        for (int j = 1; j < length; ++j) {
            file << static_cast<char>(charset[char_dist(gen)]);
        }

        file << " ";  // Разделитель
    }

    file.close();
    return true;
}