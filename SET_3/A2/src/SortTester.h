#ifndef SORTTESTER_H_
#define SORTTESTER_H_

#include <vector>
#include <chrono>
#include <fstream>
#include <functional>
#include <iostream>
#include "ArrayGenerator.h"

class SortTester {
 private:
    ArrayGenerator& generator;
    int runs;
 public:
    explicit SortTester(ArrayGenerator& gen, int num_runs = 7)
        : generator(gen), runs(num_runs) {}

    void testMergeSort(const std::function<void(std::vector<int>&, int, int,int )>& merge_sort,
                       const std::string& prefix) {
        const int max_n = 100000;
        std::ofstream fout_random(prefix + "_random.csv");
        std::ofstream fout_decreasing(prefix + "_decreasing.csv");
        std::ofstream fout_almost(prefix + "_almost.csv");

        fout_random     << "n,time_ms\n";
        fout_decreasing << "n,time_ms\n";
        fout_almost     << "n,time_ms\n";

        for (int n = 500; n <= max_n; n += 100) {
            long long sum_random = 0, sum_decreasing = 0, sum_almost = 0;

            for (int it = 0; it < runs; it++) {
                {
                    auto v = generator.GetRandomVector(n);
                    auto start = std::chrono::high_resolution_clock::now();
                    merge_sort(v, 0, v.size(), 1);
                    auto elapsed = std::chrono::high_resolution_clock::now() - start;
                    sum_random += std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
                }

                {
                    auto v = generator.GetDecreasingVector(n);
                    auto start = std::chrono::high_resolution_clock::now();
                    merge_sort(v, 0, v.size(), 1);
                    auto elapsed = std::chrono::high_resolution_clock::now() - start;
                    sum_decreasing += std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
                }

                {
                    auto v = generator.GetAlmostSortedVector(n);
                    auto start = std::chrono::high_resolution_clock::now();
                    merge_sort(v, 0, v.size(), 1);
                    auto elapsed = std::chrono::high_resolution_clock::now() - start;
                    sum_almost += std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
                }
            }

            fout_random     << n << "," << (sum_random / runs) / 1000.0 << "\n";
            fout_decreasing << n << "," << (sum_decreasing / runs) / 1000.0 << "\n";
            fout_almost     << n << "," << (sum_almost / runs) / 1000.0 << "\n";

            std::cerr << "Done n=" << n << "\n";
        }
    }

    // Гибридный merge+insertion sort с параметром threshold
    void testHybridMergeSort(const std::function<void(std::vector<int>&, int, int, int)>& merge_sort,
                             int threshold, const std::string& prefix) {
        const int max_n = 100000;
        std::ofstream fout_random(prefix + "_random.csv");
        std::ofstream fout_decreasing(prefix + "_decreasing.csv");
        std::ofstream fout_almost(prefix + "_almost.csv");

        fout_random     << "n,time_ms\n";
        fout_decreasing << "n,time_ms\n";
        fout_almost     << "n,time_ms\n";

        for (int n = 500; n <= max_n; n += 500) { // 500, так как 100 долговато
            long long sum_random = 0, sum_decreasing = 0, sum_almost = 0;

            for (int it = 0; it < runs; it++) {
                {
                    auto v = generator.GetRandomVector(n);
                    auto start = std::chrono::high_resolution_clock::now();
                    merge_sort(v, 0, v.size(), threshold);
                    auto elapsed = std::chrono::high_resolution_clock::now() - start;
                    sum_random += std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
                }

                {
                    auto v = generator.GetDecreasingVector(n);
                    auto start = std::chrono::high_resolution_clock::now();
                    merge_sort(v, 0, v.size(), threshold);
                    auto elapsed = std::chrono::high_resolution_clock::now() - start;
                    sum_decreasing += std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
                }

                {
                    auto v = generator.GetAlmostSortedVector(n);
                    auto start = std::chrono::high_resolution_clock::now();
                    merge_sort(v, 0, v.size(), threshold);
                    auto elapsed = std::chrono::high_resolution_clock::now() - start;
                    sum_almost += std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
                }
            }

            fout_random     << n << "," << (sum_random / runs) / 1000.0 << "\n";
            fout_decreasing << n << "," << (sum_decreasing / runs) / 1000.0 << "\n";
            fout_almost     << n << "," << (sum_almost / runs) / 1000.0 << "\n";

            std::cerr << "Done n=" << n << " (threshold=" << threshold << ")\n";
        }
    }
};

#endif // SORTTESTER_H_
