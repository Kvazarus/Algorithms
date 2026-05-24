#ifndef STRINGSORTANALYSIS__MSDRADIXQUICKSEARCH_H_
#define STRINGSORTANALYSIS__MSDRADIXQUICKSEARCH_H_

#include <vector>
#include <string>
#include <algorithm>
#include <random>

#include "StringTernaryQuickSearch.h"

using namespace std;

class MSDRadixQuickSort {
 private:
    static void recursion(vector<string> &arr, int L, int left, int right, vector<string> &temp, long long &comps) {
        if (right - left < 74) {
            StringTernaryQuickSort::quickSortRec(arr, L, left, right, comps);
            return;
        }
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

            vector<int> count(128);
            vector<int> start_idx(128);

            for (int ind = i; ind <= right; ind++) {
                count[arr[ind][L]]++;
            }

            start_idx[0] = left;
            for (int ind = 1; ind < 128; ind++) {
                start_idx[ind] = start_idx[ind - 1] + count[ind - 1];
            }

            vector<int> start_idx2 = start_idx;

            for (; i <= right; i++) {
                unsigned char c = arr[i][L];
                temp[start_idx[c]++] = std::move(arr[i]);
            }

            for (int ind = left; ind <= right; ind++) {
                arr[ind] = std::move(temp[ind]);
            }


            for (int ind = 0; ind < 128; ind++) {
                if (count[ind] > 1) {
                    recursion(arr, L + 1, start_idx2[ind], start_idx2[ind] + count[ind] - 1, temp, comps);
                }
            }
        }
    }

 public:
    static long long sort(vector<string> &arr) {
        long long comps = 0;
        vector<string> temp(arr.size());
        if (!arr.empty()) {
            recursion(arr, 0, 0, arr.size() - 1, temp, comps);
        }
        return comps;
    }
};

#endif //STRINGSORTANALYSIS__MSDRADIXQUICKSEARCH_H_
