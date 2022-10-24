#include <cstdlib>
#include <ctime>
#include <random>

class Generator {
public: 
    virtual int operator()() = 0;
};

class RangeGenerator : public Generator {
public:
    RangeGenerator(int l, int h) : _l(l), _h(h) { srand(time(nullptr)); }
    int operator()() override { return _l + rand() % ( _h + 1 -_l);}
private:
    int _l, _h;
};

class ArithmeticGenerator : public Generator {
public:
    ArithmeticGenerator(int first, int step) : _cur(first), _step(step) {}
    int operator()() override {
        int res = _cur;
        _cur += _step;
        return res;
    }
private:
    int _cur, _step; 
};

class NormalDistributionGenerator: public Generator {
public:
    NormalDistributionGenerator(double mean, double dev): distribution(mean, dev) {}

    int operator()() override {
        return distribution(generator);
    }
private:
    default_random_engine generator;
    normal_distribution<double> distribution;
    double min;
    double max;   
};