#ifndef STRINGSORTANALYSIS__STANDARDQUICKSORT_H_
#define STRINGSORTANALYSIS__STANDARDQUICKSORT_H_

#include <vector>
#include <string>
#include <algorithm>
#include <random>

using namespace std;

class StandardQuickSort {
 private:
    inline static mt19937 rnd;

    static bool isLess(const string &a, const string &b, long long &comps) {
        size_t min_len = min(a.size(), b.size());
        for (size_t i = 0; i < min_len; ++i) {
            comps++;
            if (a[i] != b[i]) {
                return a[i] < b[i];
            }
        }
        return a.size() < b.size();
    }

    static void quickSortRec(vector<string> &arr, int left, int right, long long &comps) {
        if (left < right) {
            string pivot = arr[rnd() % (right - left + 1) + left];
            int i = left;
            int j = right;

            while (i <= j) {
                while (isLess(arr[i], pivot, comps)) i++;
                while (isLess(pivot, arr[j], comps)) j--;
                if (i <= j) {
                    swap(arr[i], arr[j]);
                    i++;
                    j--;
                }
            }

            if (left < j) quickSortRec(arr, left, j, comps);
            if (i < right) quickSortRec(arr, i, right, comps);
        }
    }

 public:
    static long long sort(vector<string> &arr, int seed = 43985353) {
        rnd = mt19937(seed);
        long long comps = 0;
        if (!arr.empty()) {
            quickSortRec(arr, 0, arr.size() - 1, comps);
        }
        return comps;
    }
};

#endif //STRINGSORTANALYSIS__STANDARDQUICKSORT_H_
