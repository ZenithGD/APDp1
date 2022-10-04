#include "sort.hpp"

// A utility function to get maximum value from arr
//  Extracted code from https://www.geeksforgeeks.org/radix-sort/
int getMax(vector<int> &arr)
{
    int n = arr.size();
    int mx = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > mx)
            mx = arr[i];
    return mx;
}

// A function to do counting sort arr according to
// the digit represented by exp.
//  Extracted code from https://www.geeksforgeeks.org/radix-sort/
void digit_sort(vector<int> &arr, int exp)
{
    int n = arr.size();
    vector<int> output(n);
    int i, count[10] = {0};

    for (i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (i = n - 1; i >= 0; i--)
    {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    for (i = 0; i < n; i++)
        arr[i] = output[i];
}

//  Extracted code from https://www.geeksforgeeks.org/radix-sort/
void radix_sort(vector<int> &arr)
{
    // C++ implementation of Radix Sort

    int m = getMax(arr);

    // Do counting sort for every digit. Note that instead
    // of passing digit number, exp is passed. exp is 10^i
    // where i is current digit number
    for (int exp = 1; m / exp > 0; exp *= 10)
    {
        digit_sort(arr, exp);
    }
}

//  Extracted code from https://www.geeksforgeeks.org/cpp-program-for-quicksort/
int partition(vector<int> &arr, int start, int end)
{

    int pivot = arr[start];

    int count = 0;
    for (int i = start + 1; i <= end; i++)
    {
        if (arr[i] <= pivot)
            count++;
    }

    // Giving pivot element its correct position
    int pivotIndex = start + count;
    swap(arr[pivotIndex], arr[start]);

    // Sorting left and right parts of the pivot element
    int i = start, j = end;

    while (i < pivotIndex && j > pivotIndex)
    {

        while (arr[i] <= pivot)
        {
            i++;
        }

        while (arr[j] > pivot)
        {
            j--;
        }

        if (i < pivotIndex && j > pivotIndex)
        {
            swap(arr[i++], arr[j--]);
        }
    }

    return pivotIndex;
}

//  Extracted code from https://www.geeksforgeeks.org/cpp-program-for-quicksort/
void quickSortaux(vector<int> &arr, int start, int end)
{
    // C++ Implementation of the Quick Sort Algorithm.

    if (start >= end)
        return;

    int p = partition(arr, start, end);

    quickSortaux(arr, start, p - 1);

    quickSortaux(arr, p + 1, end);
}

//  Extracted code from https://www.geeksforgeeks.org/cpp-program-for-quicksort/
void quick_sort(vector<int> &arr)
{

    quickSortaux(arr, 0, arr.size() - 1);
}

//  Extracted code from https://www.techiedelight.com/es/count-sort-cpp-java-implementation/
void count_sort(vector<int> &input)
{
    // create an empty map, to collect the frequency of the array's elements
    map<int, int> freq;

    // collect distinct values in the input array as a key and their frequency as values
    for (int x : input)
    {
        freq[x]++;
    }

    // iterate through map and overwrite the input array with sorted elements
    // ( the map will iterate according to the order of the keys )
    int i = 0;
    for (auto p : freq)
    {
        while (p.second--)
        {
            input[i++] = p.first;
        }
    }
}
