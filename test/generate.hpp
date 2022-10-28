#pragma once
using namespace std;

#include <generator/generator.hpp>

vector<int> generateArray(unsigned int n, Generator& g);

void generateTest(const string name, unsigned int n, Generator& g);