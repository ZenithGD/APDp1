#include "generator.hpp"

void genQSBestCaseSorted(vector<int>& v, int begin, int end)
{
    auto count = end - begin;
    if (count < 3)
        return;

    auto middle_index = (count - 1) / 2;
    auto middle = begin + middle_index;

    //Make the left part best-case first
    genQSBestCaseSorted(v, begin, middle);

    //Swap the pivot and the start element
    std::swap(v[begin], v[middle]);

    //Make the right part best-case, too
    genQSBestCaseSorted(v, ++middle, end);
}

vector<int> genQSBestCase(unsigned int n)
{
    // generate numbers from 1 to n
    vector<int> v(n);

    iota(v.begin(), v.end(), 1);

    genQSBestCaseSorted(v, 0, n);

    return v;
}