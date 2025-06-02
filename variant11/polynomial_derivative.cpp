#include "polynomial_derivative.h"
#include <fstream>
#include <random>
#include <cmath>


int calculate_polynomial_derivative(const std::string& file_path, double x, double* derivative) {
    std::ifstream file(file_path);
    if (!file.is_open()) {
        return -1;
    }

    std::vector<double> coefficients;
    double coeff;

    while (file >> coeff) {
        coefficients.push_back(coeff);
    }

    file.close();

    if (coefficients.empty()) {
        return -2;
    }

    double result = 0.0;
    int n = coefficients.size() - 1;

    for (int i = 0; i < n; ++i) {
        result += (n - i) * coefficients[i] * std::pow(x, n - i - 1);
    }

    *derivative = result;
    return 0;
}

bool generate_polynomial_test_file(const std::string& output_path, int degree, double min_coeff, double max_coeff) {
    std::ofstream file(output_path);
    if (!file.is_open()) {
        return false;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> coeff_dist(min_coeff, max_coeff);

    for (int i = 0; i <= degree; ++i) {
        file << coeff_dist(gen) << " ";
    }

    file.close();
    return true;
}