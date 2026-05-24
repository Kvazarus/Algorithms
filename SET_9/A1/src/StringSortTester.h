#ifndef STRINGSORTANALYSIS__STRINGSORTTESTER_H_
#define STRINGSORTANALYSIS__STRINGSORTTESTER_H_

#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <algorithm>

#include "StringGenerator.h"
#include "StandardQuickSort.h"
#include "StandardMergeSort.h"
#include "StringTernaryQuickSearch.h"
#include "StringMergeSort.h"
#include "MSDRadixSort.h"
#include "MSDRadixQuickSearch.h"

using namespace std;
using namespace std::chrono;

class StringSortTester {
 private:
    int max_size;
    int step;
    int iterations;

    template<typename Sorter>
    void runBenchmark(const string &algo_name, const string &data_type, const vector<string> &data, ofstream &out_csv) {
        long long total_time_us = 0;
        long long total_comps = 0;

        for (int i = 0; i < iterations; ++i) {
            vector<string> arr = data;

            auto start = high_resolution_clock::now();
            long long comps = Sorter::sort(arr);
            auto end = high_resolution_clock::now();

            total_time_us += duration_cast<microseconds>(end - start).count();
            total_comps += comps;
        }

        long long avg_time = total_time_us / iterations;
        long long avg_comps = total_comps / iterations;

        cout << left << setw(25) << algo_name
             << setw(15) << data_type
             << setw(10) << data.size()
             << setw(15) << avg_time
             << avg_comps << "\n";

        out_csv << algo_name << "," << data_type << "," << data.size() << "," << avg_time << "," << avg_comps << "\n";
    }

 public:
    explicit StringSortTester(int _max_size = 3000, int _step = 100, int _iters = 10)
        : max_size(_max_size), step(_step), iterations(_iters) {}

    void RunAllTests(const string &filename = "benchmark_results.csv") {
        ofstream out(filename);
        if (!out.is_open()) {
            cerr << "Cannot open file for writing: " << filename << "\n";
            return;
        }

        out << "Algorithm,DataType,Size,Time_us,Comparisons\n";

        cout << string(80, '-') << "\n";
        cout << left << setw(25) << "ALGORITHM"
             << setw(15) << "DATA_TYPE"
             << setw(10) << "SIZE"
             << setw(15) << "TIME(us)"
             << "COMPARISONS\n";
        cout << string(80, '-') << "\n";

        cout << "Generating test data...\n";
        StringGenerator generator(max_size);
        cout << "Data generated. Starting benchmarks...\n";
        cout << string(80, '-') << "\n";

        auto testAllAlgorithms = [&](const string &data_type, const vector<string> &data) {
            runBenchmark<StandardQuickSort>("Standard QuickSort", data_type, data, out);
            runBenchmark<StandardMergeSort>("Standard MergeSort", data_type, data, out);
            runBenchmark<StringMergeSort>("String MergeSort", data_type, data, out);
            runBenchmark<StringTernaryQuickSort>("Ternary QuickSort", data_type, data, out);
            runBenchmark<MSDRadixSort>("MSD Radix Sort", data_type, data, out);
            runBenchmark<MSDRadixQuickSort>("MSD Radix+Quick", data_type, data, out);
            cout << string(80, '-') << "\n";
        };

        for (int current_size = step; current_size <= max_size; current_size += step) {

            vector<string> random_data = generator.GetRandomStrings(current_size);
            vector<string> reverse_data = generator.GetReverseSortedStrings(current_size);
            vector<string> almost_data = generator.GetAlmostSortedStrings(current_size);

            testAllAlgorithms("Random", random_data);
            testAllAlgorithms("Reversed", reverse_data);
            testAllAlgorithms("Almost", almost_data);
        }

        cout << "Benchmarks finished! Results saved to " << filename << "\n";
        out.close();
    }
};

#endif //STRINGSORTANALYSIS__STRINGSORTTESTER_H_