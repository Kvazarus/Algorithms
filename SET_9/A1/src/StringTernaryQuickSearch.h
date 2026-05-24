#ifndef STRINGSORTANALYSIS__STRINGTERNARYQUICKSEARCH_H_
#define STRINGSORTANALYSIS__STRINGTERNARYQUICKSEARCH_H_

#include <vector>
#include <string>
#include <algorithm>
#include <random>

using namespace std;

class StringTernaryQuickSort {
 private:
    inline static mt19937 rnd;

 public:
    static void quickSortRec(vector<string> &arr, int L, int left, int right, long long &comps) {
        if (left < right) {
            int i = left;

            for (int ind = left; ind <= right; ind++) {
                if (arr[ind].size() == L) {
                    swap(arr[ind], arr[i]);
                    i++;
                }
            }
            if (i >= right) {
                return;
            }

            left = i;

            string pivot = arr[rnd() % (right - left + 1) + left];
            char p_char = pivot[L];
            int lt = i;
            int gt = right;

            while (i <= gt) {
                char c = arr[i][L];

                comps++;
                if (p_char > c) {
                    swap(arr[lt++], arr[i++]);
                } else {
                    comps++;
                    if (p_char < c) {
                        swap(arr[gt--], arr[i]);
                    } else {
                        i++;
                    }
                }
            }

            quickSortRec(arr, L, left, lt - 1, comps);
            quickSortRec(arr, L + 1, lt, gt, comps);
            quickSortRec(arr, L, gt + 1, right, comps);
        }
    }

    static long long sort(vector<string> &arr, int seed = 43985353) {
        rnd = mt19937(seed);
        long long comps = 0;
        if (!arr.empty()) {
            quickSortRec(arr, 0, 0, arr.size() - 1, comps);
        }
        return comps;
    }
};

#endif //STRINGSORTANALYSIS__STRINGTERNARYQUICKSEARCH_H_
