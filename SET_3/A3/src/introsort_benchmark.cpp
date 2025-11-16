//#pragma GCC optimize("O3") // Ofast
//#pragma GCC target("avx2")
//#define _GLIBCXX_DEBUG

//#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <numeric>
#include <queue>
#include <set>
#include <string>
#include <random>
#include <iomanip>
#include <cmath>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <fstream>
#include <chrono>
#include <cassert>
#include <stack>
#include <cstring>

#include "ArrayGenerator.h"
#include "SortTester.h"

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ui = unsigned int;
using ld = long double;
//using bi = __int128; // big int :)

//random_device rd;
//mt19937 rnd(rd());

// #define int long long

//#define pii pair<int, int>

mt19937 rnd(23096872);

void quick_sort(vector<int>& mas, int l, int r) {
    if (r - l <= 1) return;

    int pivot_index = rnd() % (r - l) + l;
    swap(mas[pivot_index], mas[r - 1]);
    int pivot = mas[r - 1];

    int i = l;
    for (int j = l; j < r - 1; j++) {
        if (mas[j] <= pivot) {
            swap(mas[i], mas[j]);
            i++;
        }
    }
    swap(mas[i], mas[r - 1]);

    quick_sort(mas, l, i);
    quick_sort(mas, i + 1, r);
}



void heapify(vector<int>& A, int i, int l, int r) {
    int n = r - l;
    int largest = i;

    int left  = l + 2 * (i - l) + 1;
    int right = l + 2 * (i - l) + 2;

    if (left < r && A[left] > A[largest]) largest = left;
    if (right < r && A[right] > A[largest]) largest = right;

    if (largest != i) {
        swap(A[i], A[largest]);
        heapify(A, largest, l, r);
    }
}

void introsort(vector<int>& mas, int l, int r, int depth) { // [l, r)
    //INSERTION SORT
    if (r - l < 16) {
        for (int i = l + 1; i < r; i++) {
            int key = mas[i];
            int j = i - 1;
            while (j >= l && mas[j] > key) {
                mas[j + 1] = mas[j];
                j--;
            }
            mas[j + 1] = key;
        }
        return;
    }

    // QUICK SORT
    if (depth > 0) {
        int pivot_index = rnd() % (r - l) + l;
        swap(mas[pivot_index], mas[r - 1]);
        int pivot = mas[r - 1];

        int i = l;
        for (int j = l; j < r - 1; j++) {
            if (mas[j] <= pivot) {
                swap(mas[i], mas[j]);
                i++;
            }
        }
        swap(mas[i], mas[r - 1]);

        introsort(mas, l, i, depth - 1);
        introsort(mas, i + 1, r, depth - 1);
        return;
    }


    // HEAP SORT
    int n = r - l;
    for (int i = l + n / 2 - 1; i >= l; i--)
        heapify(mas, i, l, r);

    for (int i = r - 1; i > l; i--) {
        swap(mas[l], mas[i]);
        heapify(mas, l, l, i);
    }
}

void solve() {
    const int max_n = 100000;
    ArrayGenerator array_generator(max_n, 0, 10000);
    SortTester tester(array_generator);

    tester.testIntrosort(introsort,  "introsort");
}


//#define kvazadebug

signed main() {
#ifdef kvazadebug
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
//    cout << fixed << setprecision(10);

    int t = 1; // cin >> t;
    while (t--) {
        solve();
//        if (solve()) {
//            cout << "YES" << endl;
//        } else {
//            cout << "NO" << endl;
//        }
    }

    return 0;
}

