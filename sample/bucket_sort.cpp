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
    vector<double> data(size);
    if(argv[3] != nullptr){
        if(string(argv[3]) == "g"){
            normal_distribution<> distribution(0.5, 0.1);
            generate(data.begin(), data.end(), [&distribution, &generator](){
                return distribution(generator);
            });
        }
        else{
            uniform_real_distribution<double> distribution(0, 1);
            generate(data.begin(), data.end(), [&distribution, &generator](){
                return distribution(generator);
            });
        }
    }
    else{
        std::cout << "enter disribution" << '\n';
    }
    // cout << "before sort : " << endl;
    // copy(data.begin(), data.end(), ostream_iterator<double>(cout, " "));
    auto start = Time::now();
    bucket_sort(data.begin(), data.end());
    auto end   = Time::now();
    fms time = end - start;
    cout << time.count() << '\n';
    return 0;
}
