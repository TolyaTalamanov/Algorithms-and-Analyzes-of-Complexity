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
            std::cout << "gauss" << '\n';
            normal_distribution<> distribution(0.5, 0.3);
            generate(data.begin(), data.end(), [&distribution, &generator](){
                double randVal;
                do{
                    randVal = distribution(generator);
                }while(randVal > 1 || randVal < 0);
                return randVal;
            });
        }
        else{
            std::cout << "uniform" << '\n';
            uniform_real_distribution<double> distribution(0, 1);
            generate(data.begin(), data.end(), [&distribution, &generator](){
                return distribution(generator);
            });
        }
    }
    else{
        std::cout << "enter disribution" << '\n';
    }
    std::cout << "size array = " << data.size() << '\n';
    auto start = Time::now();
    opt_bucket_sort(data.begin(), data.end());
    auto end   = Time::now();
    // copy(data.begin(), data.end(), ostream_iterator<double>(cout, " "));
    fms time = end - start;
    cout << time.count() << '\n';

    return 0;
}
