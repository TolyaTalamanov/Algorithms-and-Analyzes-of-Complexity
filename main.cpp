#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <queue>
#include <chrono>
#include <iterator>
using namespace std;

using Time = std::chrono::high_resolution_clock;
using ms   = std::chrono::milliseconds;
using fms  = std::chrono::duration<float, milli>;

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
    vector<double> *buckets[n];
    std::cout << "size = " << n << '\n';

    for ( int i = 0; i < n; i++ )
        buckets[i] = new vector<double>();

    long index;

    Iterator it = first;

    while(it != last){
        index = n * (*it);
        std::cout << "buckets[ " << index << " ] = " << *it << '\n';
        buckets[index]->push_back(*it);
        it++;
    }

    for(auto& bucket : buckets){
      // insert_sor(bucket->begin(), bucket->end());
      std::cout << "before sort : " << '\n';
      copy(bucket->begin(), bucket->end(), ostream_iterator<double>(cout, " " ));
      sort(bucket->begin(), bucket->end());
      std::cout << "" << '\n';
      std::cout << "after sort : " << '\n';
      copy(bucket->begin(), bucket->end(), ostream_iterator<double>(cout, " " ));
      std::cout << "" << '\n';
    }

    it = first;
    
    for(auto& bucket : buckets){
        for(long long i = 0; i < bucket->size(); ++i){
            *it = (*bucket)[i];
            ++it;
        }
    }
    for ( int i = 0; i < n; i++ )
        delete buckets[i];
}

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
    std::cout << "array : " << '\n';
    copy(data.begin(), data.end(), ostream_iterator<double>(cout, " "));

    auto start = Time::now();
    bucket_sort(data.begin(), data.end());
    auto end   = Time::now();

    fms time = end - start;
    std::cout << "\nsorted array : " << '\n';
    copy(data.begin(), data.end(), ostream_iterator<double>(cout, " "));
    cout << "" << '\n';

    return 0;
}
