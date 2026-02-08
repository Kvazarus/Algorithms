#include <iostream>
#include <cstdint>
#include <map>
#include <unordered_map>
#include <string>
#include <vector>
#include <set>
#include <unordered_set>
#include <random>
#include <cassert>
#include <iomanip>
#include <fstream>

using namespace std;

class RandomStreamGen {
  const string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-";
  size_t total_size;
  mt19937 rnd;
  size_t given_count = 0;

public:
  RandomStreamGen(size_t size, size_t seed) : total_size(size) {
    rnd = mt19937(seed);
  }

  string get_generated_string() {
    int l = rnd() % 30 + 1;
    string s;
    for (int i = 0; i < l; i++) {
      s += charset[rnd() % charset.size()];
    }
    return s;
  }

  vector<string> get_part(double percent) {
    int cnt_now = percent * total_size;

    vector<string> mas;

    for (int i = 0; i < cnt_now; i++) {
      if (given_count + i >= total_size) return mas;
      mas.push_back(get_generated_string());
      given_count++;
    }
    return mas;
  }
};

// Сделано на основе FNV-1a
// https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function
class HashFuncGen {
  const uint32_t FNV_prime = 16777619;
  const uint32_t FNV_offset_basis = 2166136261;

public:
  uint32_t operator()(const string& str) const {
    uint32_t hash = FNV_offset_basis;

    for (auto c : str) {
      hash ^= c;
      hash *= FNV_prime;
    }

    return hash;
  }
};


/*
 * Обоснование выбора B: так как обычно для HyperLogLog берут B от 4 до 16, то я взял среднее - 10
 * Плюсом к этому, 10 просто красивое число, мне оно нравится))
 * Ну и по формуле теоретическая ошибка составляет примерно 3.25%, что звучит довольно неплохо
 */
class HyperLogLog {
  const int B = 10;
  const int m = 1024; // 2^B
  HashFuncGen hash_func;
  vector<uint32_t> regs;

public:
  HyperLogLog() {
    regs.resize(m);
  }

  void add_string(const string& s) {
    uint32_t h = hash_func(s);
    uint32_t x = (h >> (32 - B));
    uint32_t val = h << B;
    uint32_t y;
    if (val == 0) {
      y = 32 - B + 1;
    } else {
      y = __builtin_clz(val) + 1;
    }
    regs[x] = max(regs[x], y);
  }

  double estimate() {
    double ans = 0.709;
    ans *= m * m;
    double z = 0;
    for (int i = 0; i < m; i++) {
      z += 1. / ((uint32_t) 1 << regs[i]);
    }
    ans /= z;
    return ans;
  }
};

int get_exact_count(unordered_set<string>& st) {
  return st.size();
}

void Solve() {
  int num_trials = 50;
  int steps = 20;
  int total_elements = 100000;
  vector<vector<double>> results(steps, vector<double>(num_trials));
  vector<int> exact_counts(steps);

  for (int t = 0; t < num_trials; ++t) {
    HyperLogLog hll;
    RandomStreamGen gen(total_elements, t + 1337);
    unordered_set<string> exact_set;

    for (int s = 0; s < steps; ++s) {
      vector<string> part = gen.get_part(1.0 / steps);
      for (const auto& str : part) {
        hll.add_string(str);
        if (t == 0) exact_set.insert(str);
      }
      results[s][t] = hll.estimate();
      if (t == 0) exact_counts[s] = get_exact_count(exact_set);
    }
    if ((t + 1) % 10 == 0) cout << "Completed trial " << t + 1 << endl;
  }

  ofstream out("hll_stats.csv");
  out << "Step,Exact,Mean_Estimate,Std_Dev,Upper_Bound,Lower_Bound\n";

  for (int s = 0; s < steps; ++s) {
    // Считаем среднее (E)
    double sum = 0;
    for (int t = 0; t < num_trials; ++t) {
      sum += results[s][t];
    }
    double mean = sum / num_trials;

    double variance_sum = 0;
    for (int t = 0; t < num_trials; ++t) {
      variance_sum += pow(results[s][t] - mean, 2);
    }
    double std_dev = sqrt(variance_sum / num_trials);

    out << (s + 1) * (100 / steps) << "%,"
        << exact_counts[s] << ","
        << fixed << setprecision(2) << mean << ","
        << std_dev << ","
        << mean + std_dev << ","
        << mean - std_dev << "\n";
  }

  out.close();
}

signed main() {
  std::ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  Solve();
  return 0;
}