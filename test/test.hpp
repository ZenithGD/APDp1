#pragma once

#include <iostream>
#include <vector>
#include <functional>

using namespace std;

// Load test from file in path
vector<int> load_test(const string path);

void save_test(const vector<int>& vec, const string path);

// Run a test with test function
bool run_test(function<void(vector<int>&)> sort_alg, vector<int> vec);