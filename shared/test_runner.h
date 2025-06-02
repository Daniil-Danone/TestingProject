#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <functional>
#include <chrono>
#include <iomanip>

struct TestResult {
    std::string test_name;
    bool success;
    std::string message;
    double execution_time;
};

class TestRunner {
public:
    TestRunner(const std::string& output_file, bool append = false);
    ~TestRunner();

    void run_test(const std::string& name, std::function<bool()> test_func);
    void run_test_with_time(const std::string& name, std::function<bool()> test_func);
    void write_results();

private:
    std::string output_file_;
    std::vector<TestResult> results_;
    std::ofstream out_;
}; 