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

void merge_sort(vector<int>& mas, int l, int r, int threshold = 1) { // [l, r)
    if (r - l <= threshold) {
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

    int m = r - (r - l) / 2;
    merge_sort(mas, l, m);
    merge_sort(mas, m, r);

    vector<int> new_mas;
    new_mas.reserve(r - l);
    int idx1 = l;
    int idx2 = m;
    while (idx1 < m && idx2 < r) {
        new_mas.push_back((mas[idx1] <= mas[idx2]) ? mas[idx1++] : mas[idx2++]);
    }
    while (idx1 < m) {
        new_mas.push_back(mas[idx1++]);
    }
    while (idx2 < r) {
        new_mas.push_back(mas[idx2++]);
    }

    for (int i = 0; i < r - l; i++) {
        mas[i + l] = new_mas[i];
    }
}


void solve() {
    const int max_n = 100000;
    ArrayGenerator array_generator(max_n, 0, 10000);

    const int RUNS = 7;

    ofstream fout_random("merge_random.csv");
    ofstream fout_decreasing("merge_decreasing.csv");
    ofstream fout_almost("merge_almost.csv");

    fout_random << "n,time_ms\n";
    fout_decreasing << "n,time_ms\n";
    fout_almost << "n,time_ms\n";

    for (int n = 500; n <= max_n; n += 100) {

        long long sum_random = 0;
        long long sum_decreasing = 0;
        long long sum_almost = 0;

        for (int it = 0; it < RUNS; it++) {
            {
                auto v = array_generator.GetRandomVector(n);
                auto start = chrono::high_resolution_clock::now();
                merge_sort(v, 0, v.size());
                auto elapsed = chrono::high_resolution_clock::now() - start;
                sum_random += chrono::duration_cast<chrono::microseconds>(elapsed).count();
            }

            {
                auto v = array_generator.GetDecreasingVector(n);
                auto start = chrono::high_resolution_clock::now();
                merge_sort(v, 0, v.size());
                auto elapsed = chrono::high_resolution_clock::now() - start;
                sum_decreasing += chrono::duration_cast<chrono::microseconds>(elapsed).count();
            }

            {
                auto v = array_generator.GetAlmostSortedVector(n);
                auto start = chrono::high_resolution_clock::now();
                merge_sort(v, 0, v.size());
                auto elapsed = chrono::high_resolution_clock::now() - start;
                sum_almost += chrono::duration_cast<chrono::microseconds>(elapsed).count();
            }
        }

        fout_random << n << "," << (sum_random / RUNS) / 1000.0 << "\n";
        fout_decreasing << n << "," << (sum_decreasing / RUNS) / 1000.0 << "\n";
        fout_almost << n << "," << (sum_almost / RUNS) / 1000.0 << "\n";

        cerr << "Done n=" << n << "\n";
    }
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

