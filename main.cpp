#include <iostream>
#include <vector>
#include <sort/sort.hpp>
#include <test/test.hpp>

#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{

    srand(time(nullptr));

    vector<int> arr1;

    for (int i = 0; i < 10000000; i++)
    {
        arr1.push_back(rand());
    }

    if (run_test(quick_sort, arr1))
    {
        cout << ":D" << endl;
    }
    else
    {
        cout << "D:" << endl;
    }

    return 0;
}