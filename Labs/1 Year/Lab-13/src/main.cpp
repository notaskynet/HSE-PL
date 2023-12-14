#include "merge_sort.hpp"

#include <iostream>
#include <vector>
#include <chrono>


std::chrono::duration<double> calcDuration(void (*sort)(std::vector<int>&vec), std::vector<int>&vec) {
    auto start = std::chrono::steady_clock::now();
    sort(vec);
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> duration = end - start;
    return duration;
}

void fill(std::vector<int> &vec) {
    for(auto &v: vec)
        v = rand() % 100'000;
}

int main()
{
    size_t min_vector_size = 10;
    size_t max_vector_size = 100'000'000;

    while(min_vector_size <= max_vector_size) {
        std::vector<int> arr1(min_vector_size), arr2(min_vector_size);
        fill(arr1);
        fill(arr2);

        std::cout <<  calcDuration(mergeSort, arr1).count() / calcDuration(parallelMergeSort, arr2).count()<< std::endl;
        /*
        std::cout << "Size of vectors: " << min_vector_size << std::endl;

        std::cout << "====== Merge Sort ======" << std::endl;
        std::cout << calcDuration(mergeSort, arr1).count() << " s" << std::endl;
        
        std::cout << "====== MultiThread Merge Sort ======" << std::endl;
        std::cout << calcDuration(parallelMergeSort, arr2).count() << " s" << std::endl;
        */
        min_vector_size *= 10;
    }
    
    return 0;
}