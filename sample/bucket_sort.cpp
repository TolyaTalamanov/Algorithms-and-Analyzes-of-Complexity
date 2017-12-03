#include <iostream>
#include <vector>
#include <random>
#include "sorts.h"
using namespace std;

int main(int argc, char** argv) {
    long long size;
    int seed;
    if(argc > 2) {
        size     = atoi(argv[1]);
        int seed = atoi(argv[2]);
    }
    else
        cerr << "Enter size and seed" << endl;

    mt19937 generator(seed);
    uniform_real_distribution<double> distribution(0, 1);
    vector<double> data(size);

    generate(data.begin(), data.end(), [&distribution, &generator](){
        return distribution(generator);
    });

//    cout << "before sort : " << endl;
//    copy(data.begin(), data.end(), ostream_iterator<double>(cout, " "));
    auto start = Time::now();
    bucket_sort(data.begin(), data.end());
    auto end   = Time::now();
//    cout << "\n\nafter sort : " << endl;
//    copy(data.begin(), data.end(), ostream_iterator<double>(cout, " "));
    fms time = end - start;
    cout << time.count() << '\n';
    return 0;
}
