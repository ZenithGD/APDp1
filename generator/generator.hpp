#include <cstdlib>
#include <ctime>
#include <random>
#include <vector>

using namespace std;

/**
 * @brief Parent class
 * 
 */
class Generator {
public: 
    /**
     * @brief Generate a random integer value.
     * 
     * @return int 
     */
    virtual int operator()() = 0;
};

/**
 * @brief Class that generate numbers in a range
 * 
 */
class RangeGenerator : public Generator {
public:
    /**
     * @brief Construct a new Range Generator object
     * 
     * @param l The lower bound
     * @param h The high bound
     */
    RangeGenerator(int l, int h) : _l(l), _h(h) { srand(time(nullptr)); }

    /**
     * @brief Generate a random integer value.
     * 
     * @return int 
     */
    int operator()() override { return _l + rand() % ( _h + 1 -_l);}
private:
    int _l, _h;
};

/**
 * @brief Class that generate numbers depending the Arithmetic
 * 
 */
class ArithmeticGenerator : public Generator {
public:
    /**
     * @brief Construct a new Arithmetic Generator object
     * Arithmetic Generator will generate numbers given by first + k * step,
     * where k is the number of generated values
     * @param first The first value
     * @param step The step between generated numbers
     */
    ArithmeticGenerator(int first, int step) : _cur(first), _step(step) {}
    
    /**
     * @brief Generate a random integer value.
     * 
     * @return int 
     */
    int operator()() override {
        int res = _cur;
        _cur += _step;
        return res;
    }
private:
    int _cur, _step; 
};

/**
 * @brief Class that generate numbers depending the Normal Distribution
 * 
 */
class NormalDistributionGenerator: public Generator {
public:
    /**
     * @brief Construct a new Normal Distribution Generator object
     * 
     * @param mean The mean of the normal distribution
     * @param dev The standard deviation of the normal distribution
     */
    NormalDistributionGenerator(double mean, double dev): distribution(mean, dev) {}

    /**
     * @brief Generate a random integer value.
     * 
     * @return int 
     */
    int operator()() override {
        return distribution(generator);
    }
private:
    default_random_engine generator;
    normal_distribution<double> distribution;
    double min;
    double max;   
};

// Adapted from 
// https://stackoverflow.com/questions/32556521/java-quicksort-best-case-array-generation
void genQSBestCaseSorted(vector<int>& v, int begin, int end);

vector<int> genQSBestCase(unsigned int n);