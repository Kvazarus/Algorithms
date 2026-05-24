#ifndef STRINGSORTANALYSIS__STRINGMERGESORT_H_
#define STRINGSORTANALYSIS__STRINGMERGESORT_H_

#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class StringMergeSort {
 private:
    static pair<bool, int> lcpCompare(const string &a, const string &b, int known_lcp, long long &comps) {
        size_t min_len = min(a.size(), b.size());
        for (size_t i = known_lcp; i < min_len; ++i) {
            comps++;
            if (a[i] != b[i]) {
                return {a[i] < b[i], i};
            }
        }
        return {a.size() <= b.size(), min_len};
    }

    static void merge(vector<string> &arr, int left, int mid, int right, long long &comps,
                      vector<string> &temp, vector<int> &lcp, vector<int> &temp_lcp) {
        int i = left;
        int j = mid + 1;
        int k = left;

        while (i <= mid && j <= right) {
            if (lcp[i] > lcp[j]) {
                temp_lcp[k] = lcp[i];
                temp[k++] = std::move(arr[i++]);
            } else if (lcp[i] < lcp[j]) {
                temp_lcp[k] = lcp[j];
                temp[k++] = std::move(arr[j++]);
            } else {
                auto [is_less, cur_lcp] = lcpCompare(arr[i], arr[j], lcp[i], comps);
                if (is_less) {
                    temp_lcp[k] = lcp[i];
                    lcp[j] = cur_lcp;
                    temp[k++] = std::move(arr[i++]);
                } else {
                    temp_lcp[k] = lcp[j];
                    lcp[i] = cur_lcp;
                    temp[k++] = std::move(arr[j++]);
                }
            }
        }

        while (i <= mid) {
            temp_lcp[k] = lcp[i];
            temp[k++] = std::move(arr[i++]);
        }

        while (j <= right) {
            temp_lcp[k] = lcp[j];
            temp[k++] = std::move(arr[j++]);
        }

        for (int p = left; p <= right; ++p) {
            arr[p] = std::move(temp[p]);
            lcp[p] = temp_lcp[p];
        }
    }

    static void mergeSortRec(vector<string> &arr, int left, int right, long long &comps,
                             vector<string> &temp, vector<int> &lcp, vector<int> &temp_lcp) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            mergeSortRec(arr, left, mid, comps, temp, lcp, temp_lcp);
            mergeSortRec(arr, mid + 1, right, comps, temp, lcp, temp_lcp);
            merge(arr, left, mid, right, comps, temp, lcp, temp_lcp);
        }
    }

 public:
    static long long sort(vector<string> &arr) {
        long long comps = 0;
        if (!arr.empty()) {
            vector<string> temp(arr.size());
            vector<int> lcp(arr.size(), 0);
            vector<int> temp_lcp(arr.size());

            mergeSortRec(arr, 0, arr.size() - 1, comps, temp, lcp, temp_lcp);
        }
        return comps;
    }
};

#endif //STRINGSORTANALYSIS__STRINGMERGESORT_H_