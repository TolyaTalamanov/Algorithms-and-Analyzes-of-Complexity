#ifndef  SORTS_INCLUDE_SORTS_H
#define  SORTS_INCLUDE_SORTS_H

#include <algorithm>
#include <chrono>
#include <iterator>
using namespace std;

struct Block{
    Block(long long s, long long e) : start(s), end(e), counts(0) {}
    Block() : start(0), end(0), counts(0) {}
    long long start;
    long long end;
    long long counts;
};

using Time = chrono::high_resolution_clock;
using ms   = chrono::milliseconds;
using fms  = chrono::duration<float, milli>;

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
    // double max_bucket_size = 0;
    // double min_bucket_size = 0;
    const int bucket_size = 8;
    // const int size_blocks = n / bucket_size +
    // (n % bucket_size == 0 ? 0 : n % bucket_size;

    const long long n = distance(first, last);
    // vector<double> *buckets[n];
    //auto* buckets = new vector<double>(n * bucket_size);
    vector<double> buckets(n * bucket_size);
    vector<Block> blocks(n);
    for(long long i = 0, j = 0; i < buckets.size(); i += bucket_size, j++){
        blocks[j].start  = i;
        blocks[j].end    = i + bucket_size;
    }
    // vector<pair<Iterator, Iterator>> block[];
    // for ( int i = 0; i < n; i++ )
    //     buckets[i] = new vector<double>();

    long long index;
    Iterator it = first;
    while(it != last){
        index = n * (*it);
        if(blocks[index].start + blocks[index].counts  != blocks[index].end){
            buckets[blocks[index].start + blocks[index].counts] = *it;
            blocks[index].counts++;
        }
        else{
            buckets.insert(buckets.begin() + blocks[index].end, *it);
            blocks[index].end++;
            blocks[index].counts++;
            for(long long i = index + 1; i < n; ++i ){
//               blocks[i].start += bucket_size;
//               blocks[i].end   += bucket_size;
                blocks[i].start += 1;
                blocks[i].end   += 1;

            }
        }
        //buckets[index]->push_back(*it);
        it++;
    }

    // for(auto& bucket : buckets){
    //   insert_sort(bucket->begin(), bucket->end());
    //   // if(max_bucket_size < bucket->size()){
    //   //     max_bucket_size = bucket->size();
    //   // }
    //   // if(min_bucket_size > bucket->size()){
    //   //     min_bucket_size = bucket->size();
    //   // }
    //
    //   // sort(bucket->begin(), bucket->end());
    // }
    for(long long i = 0; i < n; i++ ){
        if(blocks[i].counts != 0) {
            insert_sort(buckets.begin() + blocks[i].start, buckets.begin() + blocks[i].start + blocks[i].counts);
        }
    }
    it = first;
    for(long long i = 0; i < n; i++ ){
        if(blocks[i].counts != 0) {
            for (long long j = blocks[i].start; j <blocks[i].start + blocks[i].counts; j++) {
                *it = buckets[j];
                ++it;
            }
        }
    }
    //delete buckets;

    // it = first;
    // for(auto& bucket : buckets){
    //     for(long long i = 0; i < bucket->size(); ++i){
    //         *it = (*bucket)[i];
    //         ++it;
    //     }
    // }
    // for ( int i = 0; i < n; i++ )
    //     delete buckets[i];

    // cout << "max bucket size = " << max_bucket_size << endl;
    // cout << "min bucket size = " << min_bucket_size << endl;
}
#endif //SORTS_INCLUDE_SORTS_H
