#ifndef STRINGSORTANALYSIS__STANDARDMERGESORT_H_
#define STRINGSORTANALYSIS__STANDARDMERGESORT_H_

#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class StandardMergeSort {
 private:
    static bool isLessOrEqual(const string &a, const string &b, long long &comps) {
        size_t min_len = min(a.size(), b.size());
        for (size_t i = 0; i < min_len; ++i) {
            comps++;
            if (a[i] != b[i]) {
                return a[i] < b[i];
            }
        }
        return a.size() <= b.size();
    }

    static void merge(vector<string> &arr, int left, int mid, int right, long long &comps, vector<string> &temp) {
        int i = left;
        int j = mid + 1;
        int k = left;

        while (i <= mid && j <= right) {
            if (isLessOrEqual(arr[i], arr[j], comps)) {
                temp[k++] = std::move(arr[i++]);
            } else {
                temp[k++] = std::move(arr[j++]);
            }
        }

        while (i <= mid) {
            temp[k++] = std::move(arr[i++]);
        }

        while (j <= right) {
            temp[k++] = std::move(arr[j++]);
        }

        for (int p = left; p <= right; ++p) {
            arr[p] = std::move(temp[p]);
        }
    }

    static void mergeSortRec(vector<string> &arr, int left, int right, long long &comps, vector<string> &temp) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            mergeSortRec(arr, left, mid, comps, temp);
            mergeSortRec(arr, mid + 1, right, comps, temp);
            merge(arr, left, mid, right, comps, temp);
        }
    }

 public:
    static long long sort(vector<string> &arr) {
        long long comps = 0;
        if (!arr.empty()) {
            vector<string> temp(arr.size());
            mergeSortRec(arr, 0, arr.size() - 1, comps, temp);
        }
        return comps;
    }
};

#endif //STRINGSORTANALYSIS__STANDARDMERGESORT_H_
