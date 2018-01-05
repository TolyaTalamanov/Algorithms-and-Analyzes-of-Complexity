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
    long long buckets_size = buckets.size();
    for(long long i = 0, j = 0; i < buckets_size; i += bucket_size, j++){
        blocks[j].start  = i;
        blocks[j].end    = i + bucket_size;
    }
    // vector<pair<Iterator, Iterator>> block[];
    // for ( int i = 0; i < n; i++ )
    //     buckets[i] = new vector<double>();

    long long index;
    Iterator it = first;
//     while(it != last){
//         index = n * (*it);
//         if(blocks[index].start + blocks[index].counts  != blocks[index].end){
//             buckets[blocks[index].start + blocks[index].counts] = *it;
//             blocks[index].counts++;
//         }
//         else{
//             buckets.insert(buckets.begin() + blocks[index].end, *it);
//             blocks[index].end++;
//             blocks[index].counts++;
//             for(long long i = index + 1; i < n; ++i ){
// //               blocks[i].start += bucket_size;
// //               blocks[i].end   += bucket_size;
//                 blocks[i].start += 1;
//                 blocks[i].end   += 1;
//             }
//         }
//         //buckets[index]->push_back(*it);
//         ++it;
//     }

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
//               blocks[i].start += bucket_size;
//               blocks[i].end   += bucket_size;
                blocks[i].start += 1;
                blocks[i].end   += 1;
            }
        }
        //buckets[index]->push_back(*it);

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


//template< class Iterator >
// void opt_bucket_sort(Iterator first, Iterator last){
//     const int bucket_size = 8;
//     const int n = distance(first, last);
//     vector<double> buckets(n * bucket_size);
//     vector<int>start(n);
//     vector<int>end(n);
//     vector<int>counts(n);
//     fill(counts.begin(), counts.end(), 0);
//     int buckets_size = buckets.size();
//
//     //auto start_time = Time::now();
//     int j = 0;
//     for(int i = 0; i < buckets_size; i += bucket_size)
//     {
//         start[j]  = i;
//         end[j]    = i + bucket_size;
//         ++j;
//     }
//     // auto finish_time = Time::now();
//     // fms time = finish_time - start_time;
//     // std::cout << "loop time : " << time.count() << '\n';
//     int index;
//     Iterator it = first;
//     //#pragma omp parallel for
//
//     // for(auto it = first; it < last; ++it){
//     //     index = n * (*it);
//     //     if(start[index] + counts[index]  != end[index]){
//     //         buckets[start[index] + counts[index]] = *it;
//     //         counts[index]++;
//     //     }
//     //     else{
//     //         buckets.insert(buckets.begin() + end[index], *it);
//     //         end[index]++;
//     //         counts[index]++;
//     //         for(long long i = index + 1; i < n; ++i ){
//     //             start[i]++;
//     //             end[i]++;
//     //         }
//     //     }
//     // }
//     //#pragma omp parallel for
//     auto start_time = Time::now();
//     vector<double> input_vec(n);
//     copy(first, last, input_vec.begin());
//
//     int pos;
//     double val_it;
//     //#pragma omp parallel for schedule(static)
//     for(int i = 0; i < n; ++i){
//         val_it = input_vec[i] /**(it + i)*/;
//         index = val_it * n;
//         pos = start[index] + counts[index];
//         if(pos != end[index]){
//                 buckets[pos] = val_it;
//                 ++counts[index];
//         }
//         else{
//              buckets.insert(buckets.begin() + end[index], val_it);
//              end[index]++;
//              counts[index]++;
//              for(long long j = index + 1; j < n; ++j ){
//                  start[j]++;
//                  end[j]++;
//              }
//
//             }
//             //++it;
//     }
//     auto finish_time = Time::now();
//     fms time = finish_time - start_time;
//     std::cout << "loop time : " << time.count() << '\n';
//
//     //auto loop_start = Time::now();
//     for(int i = 0; i < n; ++i ){
//         if(counts[i] > 1) {
//             insert_sort(buckets.begin() + start[i], buckets.begin() + start[i] + counts[i]);
//         }
//     }
//     // auto loop_end = Time::now();
//     // fms loop_time = loop_end - loop_start;
//     // std::cout << "loop 2 time : " << loop_time.count() << '\n';
//     // it = first;
//     int s, e;
//
//     //auto loop_start2 = Time::now();
//     for(int i = 0; i < n; ++i ){
//         if(counts[i] != 0) {
//             s = start[i];
//             e   = s + counts[i];
//             for (int j = s ; j < e; j++) {
//                 *it = buckets[j];
//                 ++it;
//             }
//         }
//     }
//     // auto loop_end2 = Time::now();
//     // fms loop_time2 = loop_end2 - loop_start2;
//     // std::cout << "loop 3 time : " << loop_time2.count() << '\n';
//
//
// }
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
    //auto loop_start = Time::now();
    double val_it;
    for(int i = 0 ; i < n; ++i){
        val_it = *(first + i);
        index = val_it * counts_bucket;
        buckets[shifts[index]++] = val_it;
    }
//    auto loop_end = Time::now();
//    fms loop_time = loop_end - loop_start;
//    cout << "loop time = " << loop_time.count() << endl;


    current_position = 0;
    for(int i = 0 ; i < counts_bucket; ++i){
        if(current_position != shifts[i]){
            int start = current_position;
            int end   = shifts[i];
//            std::cout << "\n\nbuckets[ " << i << " ] : " << '\n';
//            std::cout << "current_pos    =  " << start << '\n';
//            std::cout << "count elements =  " << sizes[i] << '\n';
//            std::cout << "end sort index =  " << current_position + sizes[i]
//                                                                  - 1 << '\n';
////            copy(first + current_position, first +
//                                current_position + sizes[i] - 1,
//                                 ostream_iterator<double>(cout, " "));
            std::sort(buckets.begin() + start, buckets.begin() + end);
            current_position = shifts[i];

        }
    }
      copy(buckets.begin(), buckets.end(), first);
      //copy(first, last, ostream_iterator<double>(cout, " "));
//    for(int i = 0; i < n; ++i){
//        *(first + i) = buckets[i];
//    }
}

#endif //SORTS_INCLUDE_SORTS_H
