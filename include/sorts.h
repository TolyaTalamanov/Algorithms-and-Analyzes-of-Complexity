#ifndef  SORTS_INCLUDE_SORTS_H
#define  SORTS_INCLUDE_SORTS_H

#include <algorithm>
#include <chrono>
#include <iterator>
#include <omp.h>

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
    const int bucket_size = 8;
    const long long n = distance(first, last);
    vector<double> buckets(n * bucket_size);
    vector<Block> blocks(n);
    long long buckets_size = buckets.size();
    for(long long i = 0, j = 0; i < buckets_size; i += bucket_size, j++){
        blocks[j].start  = i;
        blocks[j].end    = i + bucket_size;
    }
    long long index;
    Iterator it = first;
    for(auto it = first; it < last; ++it){
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
                blocks[i].start += 1;
                blocks[i].end   += 1;
            }
        }
    }
    for(long long i = 0; i < n; i++ ){
        if(blocks[i].counts != 0) {
            insert_sort(buckets.begin() + blocks[i].start, buckets.begin() + blocks[i].start + blocks[i].counts);
        }
    }
    it = first;
    long long start, end;

    for(long long i = 0; i < n; i++ ){
        if(blocks[i].counts != 0) {
            start = blocks[i].start;
            end   = start + blocks[i].counts;
            for (long long j = start ; j < end; j++) {
                *it = buckets[j];
                ++it;
            }
        }
    }
}

template< class Iterator >
void opt_bucket_sort(Iterator first, Iterator last){
    const int n = distance(first, last);
    double scale;
    if(n <= 1)
        scale = 1;
    else if(n > 2 && n <= 1000)
        scale = 0.5;
    else if(n > 1000 && n <= 100000)
         scale = 0.25;
    else
        scale = 0.05;

    const int counts_bucket = n * scale;//sqrt(n);
    vector<double> buckets(n);
    vector<int>    sizes (counts_bucket);
    vector<int>    shifts(counts_bucket);
    int index;
    double val;
    for(int i = 0 ; i < n; ++i){
        val = *(first + i);
        index = val * counts_bucket;
        sizes[index]++;
    }
    int current_position = 0;
    for(int i = 0 ; i < counts_bucket; ++i){
        shifts[i] = current_position;
        current_position += sizes[i];
    }
    double val_it;
    for(int i = 0 ; i < n; ++i){
        val_it = *(first + i);
        index = val_it * counts_bucket;
        buckets[shifts[index]++] = val_it;
    }
    current_position = 0;
    for(int i = 0 ; i < counts_bucket; ++i){
        if(current_position != shifts[i]){
            int start = current_position;
            int end   = shifts[i];
            std::sort(buckets.begin() + start, buckets.begin() + end);
        }
    }
      copy(buckets.begin(), buckets.end(), first);
}
#endif //SORTS_INCLUDE_SORTS_H
