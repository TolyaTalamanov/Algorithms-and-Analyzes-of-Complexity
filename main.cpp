#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <queue>
#include <chrono>
#include <array>
#include <list>

using namespace std;

template<typename Iterator, typename Predicate>
void insert_sort(Iterator first, Iterator last, Predicate p){
    for(auto i = first; i != last; ++i){
        rotate(upper_bound(first, i, *i, p), i, i + 1);
    }
}

template<typename Iterator>
void insert_sort(Iterator first, Iterator last){
    insert_sort(first, last, less<typename iterator_traits<Iterator>::value_type>());
}

template< class Iterator >
void bucket_sort(Iterator first, Iterator last){
    const long long n = distance(first, last);
    vector<double> buckets[n];
    long index;

    Iterator it = first;

    while(it != last){
        index = n * (*it);
        buckets[index].push_back(*it);
        it++;
    }

    for(auto& bucket : buckets){
        insert_sort(bucket.begin(), bucket.end());
    }
    it = first;
    for(long long i = 0 ; i < n; i++){
        for(long long j = 0 ; j < buckets[i].size(); j++){
            *it++ = buckets[i][j];
        }
    }

}

int main(int argc, char** argv) {
    long long size;
    int seed;
    if(argc > 1) {
        size     = atoi(argv[1]);
        int seed = atoi(argv[2]);
    }
    else
        cerr << "Enter size" << endl;

    mt19937 generator(seed);
    uniform_real_distribution<double> distribution(0, 1);
    vector<double> data(size);
    generate(data.begin(), data.end(), [&distribution, &generator](){
        return distribution(generator);
    });

    //copy(data.begin(), data.end(), ostream_iterator<double>(cout, " "));
    auto start = std::chrono::steady_clock::now();
    //bucket_sort(data.begin(), data.end());
    sort(data.begin(), data.end());
    auto end = std::chrono::steady_clock::now();

    long long time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    cout << time << "ms" <<endl;

    return 0;
}
