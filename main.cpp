#include <iostream>
#include <iomanip>
#include <fstream>

#include <vector>
#include <sort/sort.hpp>
#include <test/test.hpp>

#include <generate.hpp>

#include <cstring>
#include <cstdlib>
#include <ctime>

using namespace std;

const int MAX = 150000;
const string GEN_PATH = "testfiles/generated/";

void generateTests() {
    RangeGenerator g1(0, 100000000);
    generateTest(GEN_PATH + "test1.txt", 10000, g1);

    ArithmeticGenerator g2(0, 1);
    generateTest(GEN_PATH + "test_step_+1.txt", 100000, g2);

    NormalDistributionGenerator g3(500, 40);
    generateTest(GEN_PATH + "test_normal_500_40.txt", 100000, g3);

    RangeGenerator g4(100000000, 999999999);
    generateTest(GEN_PATH + "test2.txt", 10000, g4);
}

// analyze quicksort for best, avg and worst cases
void analyzeQuicksort() {
    // TODO: refactor time measurement as a fn of generator and method and size
    // TODO: allow to dump results in file

    ofstream csvOut("quicksortAnalysis.csv");

    if ( !csvOut.is_open() ) {
        throw std::runtime_error("Can't open file");
    }

    csvOut << "n;avg;worst" << endl;
    
    for ( int i = 10000; i < MAX; i += 5000) {
        double init, end, stime, utime;
        // Worst case: sorted vector
        ArithmeticGenerator gsorted(0, 1);

        // Avg case: evenly distributed
        RangeGenerator guniform(1, MAX);

        auto as = generateArray(i, gsorted);

        init = clock();
        quick_sort(as);
        end = clock();
        
        stime = double(end - init) / CLOCKS_PER_SEC;

        auto au = generateArray(i, guniform);

        init = clock();
        quick_sort(au);
        end = clock();

        utime = double(end - init) / CLOCKS_PER_SEC;

        csvOut << i << ";" << setprecision(10) << utime << ";" << setprecision(10) << stime << endl;
    }

    csvOut.close();
}

void analyzeRadix() {

    ofstream csvOut("radixAnalysis.csv");

    if ( !csvOut.is_open() ) {
        throw std::runtime_error("Can't open file");
    }

    csvOut << "n;best;avg;worst" << endl;

    for ( int i = 10000; i < MAX; i += 5000) {
        double init, end, besttime, worsttime, avgtime;

        // Avg case: evenly distributed
        RangeGenerator guniform(1, MAX);
        // Mixed
        auto avgCase = generateArray(i, guniform);

        init = clock();
        radix_sort(avgCase);
        end = clock();

        avgtime = double(end - init) / CLOCKS_PER_SEC;
        
        // All elements have the same number of digits
        RangeGenerator guniformdigits(100000, 999999);

        auto bestCase = generateArray(i, guniformdigits);

        init = clock();
        radix_sort(bestCase);
        end = clock();
        
        besttime = double(end - init) / CLOCKS_PER_SEC;

        // One of the elements has many more digits than the others
        auto worstCase = generateArray(i-1, guniformdigits);
        worstCase.push_back(10000000);

        init = clock();
        radix_sort(worstCase);
        end = clock();

        worsttime = double(end - init) / CLOCKS_PER_SEC;

        csvOut << i << ";" << setprecision(10) << besttime << ";" << setprecision(10) << avgtime << ";" << setprecision(16) << worsttime << endl;
    }
    csvOut.close();
}

void analyzeCountSort() {

    ofstream csvOut("countAnalysis.csv");

    if ( !csvOut.is_open() ) {
        throw std::runtime_error("Can't open file");
    }
    
    csvOut << "n;best;avg;worst" << endl;
    for ( int i = 10000; i < MAX; i += 5000) {
        double init, end;

        // Best case: only one number
        ArithmeticGenerator guniform(1, 0);

        auto bestCase = generateArray(i, guniform);

        init = clock();
        count_sort(bestCase);
        end = clock();
        
        double besttime = double(end - init) / CLOCKS_PER_SEC;

        // avg Case: the range is lower
        RangeGenerator guniform2 (0, 100);
        auto avgCase = generateArray(i, guniform2);

        init = clock();
        count_sort(avgCase);
        end = clock();
        double avgtime = double(end - init) / CLOCKS_PER_SEC;
        
        // worst Case: the value of the range is bigger
        RangeGenerator guniform3 (0, 100000000);
        auto worstCase = generateArray(i, guniform3);

        init = clock();
        count_sort(worstCase);
        end = clock();

        double worsttime = double(end - init) / CLOCKS_PER_SEC;

        csvOut << i << ";" << setprecision(10) << besttime << ";" << setprecision(10) << avgtime << ";" << setprecision(16) << worsttime << endl;
    }
}

int main(int argc, char** argv)
{

    srand(time(nullptr));
    
    if ( argc < 2 ){
        cerr << "Se debe invocar el programa como: ./main {-g | -e | -a}" << endl;
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
        else if (strcmp(argv[3], "--count") == 0) {
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
    else if ( strcmp(argv[1], "-a") == 0 ) {
        // analyze cases for each 
        if ( strcmp(argv[2], "--radix") == 0 ){
            analyzeRadix();
        }
        else if (strcmp(argv[2], "--quick") == 0) {
            analyzeQuicksort();
        }
        else if (strcmp(argv[2], "--count") == 0) {
            analyzeCountSort();
        }
        else {
            cerr << "Se ha introducido una opción inválida (opciones: {--radix | --quick | --count}" << endl;
            exit(1);
        }
        
    }
    else {
        cerr << "No se reconoce la opción: debe ser -g o -e" << endl;
        exit(1);
    }
    return 0;
}