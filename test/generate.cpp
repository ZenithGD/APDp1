#include <vector>
#include <ctime>
#include <cstdlib>
#include <test/test.hpp>
#include "generate.hpp"

using namespace std;

void generateTest(const string name, unsigned int n, Generator& g){

    auto arr1 = generateArray(n, g); 
    string path = "testfiles/generated_" + name;
    cout << "CREANDO FICHERO..." << path <<endl;
    save_test(arr1, path);

}

vector<int> generateArray(unsigned int n, Generator& g) {
    vector<int> arr1;

    for (unsigned int i = 0; i < n; i++)
    {
        arr1.push_back(g());
    }

    return arr1;
}