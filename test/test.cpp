#include <test/test.hpp>

#include <fstream>

// Load test from file in path
vector<int> load_test(const string path) {

    ifstream f(path);

    vector<int> v;
    int val;

    if ( !f.is_open() ) {
        throw runtime_error("Can't open '" + path + "'");
    }
        
    while ( !f.eof() ) {
        f >> val;
        v.push_back(val);
    }

    f.close();

    return v;
}

void save_test(const vector<int>& vec, const string path) {
    ofstream out(path);

    if ( !out.is_open() ) {
        throw runtime_error("Can't open '" + path + "'");
    }

    for ( int i = 0; i < vec.size(); i++ ) {
        out << vec[i];
        if ( i != vec.size() - 1 ) {
            out << " ";
        }
    }
    

    out.close();
}

// Check that the elements of the vector are sorted
bool check_sorted(vector<int>& vec) {
    bool ok = true;
    int n = vec.size();

    for ( int i = 0; i < n-1 && ok; i++){
        if(vec[i] > vec[i + 1]) {
            ok = false;
        }
    }

    return ok;
}

void print_array(vector<int> arr, int n) {
    for ( int i = 0; i < n; i++ ) {
        cout << arr[i] << ", ";
    }
    cout << endl;
}

// Run a test with test function
bool run_test(function<void(vector<int>&)> sort_alg, vector<int> vec) {

    try {
        sort_alg(vec);
        
        return check_sorted(vec);
    } catch (exception& ex) {
        cout << ex.what() << endl;
        return false;
    }
}