#ifndef STRINGSORTANALYSIS__STRINGGENERATOR_H_
#define STRINGSORTANALYSIS__STRINGGENERATOR_H_

#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include <cassert>

using namespace std;

class StringGenerator {
 private:
    string alphabet = "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz0123456789!@#%:;^&*()-.";
    mt19937 rnd;
    vector<string> random_strings;
    vector<string> reverse_sorted_string;
    vector<string> almost_sorted_strings;
    int max_n;

    string createString(int n) {
        string s;
        s.reserve(n);
        for (int i = 0; i < n; i++) {
            s += alphabet[rnd() % alphabet.size()];
        }
        return s;
    }

 public:
    explicit StringGenerator(int _max_n = 3000, int len_min = 10, int len_max = 200, int seed = 198354723) : max_n(
        _max_n) {
        rnd = mt19937(seed);

        random_strings.reserve(max_n);
        reverse_sorted_string.reserve(max_n);
        almost_sorted_strings.reserve(max_n);

        for (int i = 0; i < max_n; i++) {
            int len1 = rnd() % (len_max - len_min + 1) + len_min;
            int len2 = rnd() % (len_max - len_min + 1) + len_min;
            int len3 = rnd() % (len_max - len_min + 1) + len_min;

            random_strings.push_back(createString(len1));
            reverse_sorted_string.push_back(createString(len2));
            almost_sorted_strings.push_back(createString(len3));
        }

        sort(reverse_sorted_string.begin(), reverse_sorted_string.end(), greater<>());

        sort(almost_sorted_strings.begin(), almost_sorted_strings.end());
        for (int i = 0; i < max_n / 10; i++) {
            int l = rnd() % max_n;
            int r = rnd() % max_n;
            swap(almost_sorted_strings[l], almost_sorted_strings[r]);
        }
    }

    vector<string> GetRandomStrings(int n) {
        assert(n <= max_n);
        vector<string> mas;
        if (n == max_n) {
            return random_strings;
        }
        mas.resize(n);
        int l = rnd() % (max_n - n + 1);
        copy(random_strings.begin() + l, random_strings.begin() + l + n, mas.begin());
        return mas;
    }

    vector<string> GetReverseSortedStrings(int n) {
        assert(n <= max_n);
        vector<string> mas;
        if (n == max_n) {
            return reverse_sorted_string;
        }
        mas.resize(n);
        int l = rnd() % (max_n - n + 1);
        copy(reverse_sorted_string.begin() + l, reverse_sorted_string.begin() + l + n, mas.begin());
        return mas;
    }

    vector<string> GetAlmostSortedStrings(int n) {
        assert(n <= max_n);
        vector<string> mas;
        if (n == max_n) {
            return almost_sorted_strings;
        }
        mas.resize(n);
        int l = rnd() % (max_n - n + 1);
        copy(almost_sorted_strings.begin() + l, almost_sorted_strings.begin() + l + n, mas.begin());
        return mas;
    }
};

#endif //STRINGSORTANALYSIS__STRINGGENERATOR_H_