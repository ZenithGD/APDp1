#pragma once

#include <iostream>
#include <vector>
#include <functional>

using namespace std;

/**
 * @brief Load test from a file specified by <path>.
 * If the file doesn't exist, this function will throw a runtime error.
 * 
 * @param path The file's path
 * @return vector<int> 
 */
vector<int> load_test(const string path);

/**
 * @brief Save test to a file specified by <path>.
 * This function will throw if the file can't be written to <path>
 * 
 * @param vec The vector
 * @param path The file's path
 */
void save_test(const vector<int> &vec, const string path);

/**
 * @brief Run a test with any sorting algorithm
 * 
 * @param sort_alg The sorting algorithm function
 * @param vec The vector
 * @return true iff the result of sort_alg is sorted in ascending order
 * @return false otherwise
 */
bool run_test(function<void(vector<int> &)> sort_alg, vector<int> vec);