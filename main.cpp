#include <iostream>
#include <vector>
#include <sort/sort.hpp>
#include <test/test.hpp>

#include <generate.hpp>

#include <cstring>
#include <cstdlib>
#include <ctime>

using namespace std;

void generateTests() {
    RangeGenerator g1(0, 100000000);
    generateTest("test1", 10000, g1);

    ArithmeticGenerator g2(0, 1);
    generateTest("test_step_+1", 100000, g2);

    NormalDistributionGenerator g3(500, 40);
    generateTest("test_normal_500_40", 100000, g3);

    RangeGenerator g4(100000000, 999999999);
    generateTest("test2", 10000, g4);
}

int main(int argc, char** argv)
{

    srand(time(nullptr));
    
    if ( argc < 2 ){
        cerr << "Se debe invocar el programa como: ./main {-g | -e}" << endl;
        exit(1);
    }
        
    if ( strcmp(argv[1], "-g") == 0 ) {
        
        generateTests();
        
    } 
    else if ( strcmp(argv[1], "-e") == 0 ) {
        
        if ( argc < 4 ) {
            cerr << "Se debe invocar el programa como: ./main -e <path> {--radix | --quick | --count}" << endl;
            exit(1);
        }

        auto arr = load_test(argv[2]);
        cout << arr.size() << endl;

        bool ok = false;
        double init, end;
        if ( strcmp(argv[3], "--radix") == 0 ){
            function<void(vector<int> &)> radixMethod(radix_sort);

            init = clock();
            ok = run_test(radixMethod, arr);
            end = clock();
        }
        else if (strcmp(argv[3], "--quick") == 0) {
            function<void(vector<int> &)> quickMethod(quick_sort);
            init = clock();
            ok = run_test(quickMethod, arr);
            end = clock();
        }
        else if (strcmp (argv[3], "--count") == 0) {
            function<void(vector<int> &)> countMethod(count_sort);
            init = clock();
            ok = run_test(countMethod, arr);
            end = clock();
        }
        else {
            cerr << "Se ha introducido una opción inválida (opciones: {--radix | --quick | --count}" << endl;
            exit(1);
        }
        
        if ( ok ) {
            double time = double(end - init) / CLOCKS_PER_SEC;
            cout << "Tiempo de ejecución del test: " << time << endl;
        }
        
        else {
            cout << "D:" << endl;
        }
    }
    else {
        cerr << "No se reconoce la opción: debe ser -g o -e" << endl;
        exit(1);
    }
    return 0;
}