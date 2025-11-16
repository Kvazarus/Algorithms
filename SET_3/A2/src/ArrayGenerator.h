#ifndef ARRAYGENERATOR_H_
#define ARRAYGENERATOR_H_

#include <vector>
#include <random>
#include <algorithm>
#include <cassert>

class ArrayGenerator {
 private:
    int max_n;
    std::vector<int> mas1;
    std::vector<int> mas2;
    std::vector<int> mas3;
    std::mt19937 rnd;

 public:
    explicit ArrayGenerator(int _max_n, int min_zn = 0, int max_zn = 10000, int seed = 13852945) : max_n(_max_n) {
        rnd = std::mt19937(seed);

        mas1.resize(max_n);
        mas2.resize(max_n);
        mas3.resize(max_n);

        for (int i = 0; i < max_n; i++) {
            mas1[i] = rnd() % (max_zn - min_zn + 1) + min_zn;
            mas2[i] = rnd() % (max_zn - min_zn + 1) + min_zn;
            mas3[i] = rnd() % (max_zn - min_zn + 1) + min_zn;
        }

        std::sort(mas2.begin(), mas2.end(), std::greater<>());

        std::sort(mas3.begin(), mas3.end());
        for (int i = 0; i < max_n / 10; i++) {
            int l = rnd() % max_n;
            int r = rnd() % max_n;
            std::swap(mas3[l], mas3[r]);
        }
    }

    std::vector<int> GetRandomVector(int n) {
        assert(n <= max_n);
        std::vector<int> mas;
        if (n == max_n) {
            mas = mas1;
            return mas;
        }
        mas.resize(n);
        int l = rnd() % (max_n - n + 1);
        std::copy(mas1.begin() + l, mas1.begin() + l + n, mas.begin());
        return mas;
    }

    std::vector<int> GetDecreasingVector(int n) {
        assert(n <= max_n);
        std::vector<int> mas;
        if (n == max_n) {
            mas = mas2;
            return mas;
        }
        mas.resize(n);
        int l = rnd() % (max_n - n + 1);
        std::copy(mas2.begin() + l, mas2.begin() + l + n, mas.begin());
        return mas;
    }

    std::vector<int> GetAlmostSortedVector(int n) {
        assert(n <= max_n);
        std::vector<int> mas;
        if (n == max_n) {
            mas = mas3;
            return mas;
        }
        mas.resize(n);
        int l = rnd() % (max_n - n + 1);
        std::copy(mas3.begin() + l, mas3.begin() + l + n, mas.begin());
        return mas;
    }
};

#endif //ARRAYGENERATOR_H_
