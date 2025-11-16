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

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ui = unsigned int;
using ld = long double;
//using bi = __int128; // big int :)

//random_device rd;
//mt19937 rnd(rd());

// #define int long long

#define pii pair<int, int>

mt19937_64 rnd(19283475);

struct Circle {
    ld x, y, r;

    bool isPointInCircle(ld px, ld py) {
        return sqrt((px - x) * (px - x) + (py - y) * (py - y)) <= r;
    }
};

struct Rect {
    ld x1, y1;
    ld x2, y2;

    ld Area() {
        return (x2 - x1) * (y2 - y1);
    }
};

ld calcApproxArea(Circle& c1, Circle& c2, Circle& c3, bool bigZone = false, int n = 1e6) {
    Rect rect;
    if (bigZone) {
        rect.x1 = min(c1.x - c1.r, min(c2.x - c2.r, c3.x - c3.r));
        rect.y1 = min(c1.y - c1.r, min(c2.y - c2.r, c3.y - c3.r));
        rect.x2 = max(c1.x + c1.r, max(c2.x + c2.r, c3.x + c3.r));
        rect.y2 = max(c1.y + c1.r, max(c2.y + c2.r, c3.y + c3.r));
    } else {
        rect.x1 = max(c1.x - c1.r, max(c2.x - c2.r, c3.x - c3.r));
        rect.y1 = max(c1.y - c1.r, max(c2.y - c2.r, c3.y - c3.r));
        rect.x2 = min(c1.x + c1.r, min(c2.x + c2.r, c3.x + c3.r));
        rect.y2 = min(c1.y + c1.r, min(c2.y + c2.r, c3.y + c3.r));
    }

    int k = n;
    int kol_good = 0;
    for (int i = 0; i < k; i++) {
        ld x = rect.x1 + ((ld) rnd() / rnd.max()) * (rect.x2 - rect.x1);
        ld y = rect.y1 + ((ld) rnd() / rnd.max()) * (rect.y2 - rect.y1);

        if (c1.isPointInCircle(x, y) && c2.isPointInCircle(x, y) && c3.isPointInCircle(x, y))
            kol_good++;
    }

    return (ld) kol_good / k * rect.Area();
}

void solve() {
    Circle c1, c2, c3;
    c1 = {1, 1, 1};
    c2 = {1.5, 2, sqrt(5) / 2};
    c3 = {2, 1.5, sqrt(5) / 2};

    ofstream fout("results.txt");

    ld S_exact = 0.25 * M_PI + 1.25 * asin(0.8) + (-1.0);

    for (int big = 0; big < 2; big++) {
        for (int n = 100; n < 100000; n += 500) {
            ld approx = calcApproxArea(c1, c2, c3, big, n);
            fout << n << " " << big << " " << approx << " " << S_exact << "\n";
        }
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
    cout << fixed << setprecision(10);

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
