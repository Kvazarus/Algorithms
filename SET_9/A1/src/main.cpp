#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>

#include "StringSortTester.h"

using namespace std;

int main() {
    StringSortTester tester;
    tester.RunAllTests("results.csv");
    return 0;
}