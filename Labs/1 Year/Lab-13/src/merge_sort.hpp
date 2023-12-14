#pragma once

#include <vector>
#include <thread>


void merge(
    std::vector<int>::iterator first1, std::vector<int>::iterator last1,
    std::vector<int>::iterator first2, std::vector<int>::iterator last2,
    std::vector<int>::iterator d_first
) {
    while(first1 != last1 && first2 != last2) {
        if( (*first1) <= (*first2) ) {
            (*d_first) = (*first1);
            ++first1; 
        } else {
            (*d_first) = (*first2);
            ++first2; 
        }
        ++d_first;
    }

    while(first1 != last1)
    {
        (*d_first) = (*first1);
        ++first1; 
    }

    while(first2 != last2)
    {
        (*d_first) = (*first2);
        ++first2; 
    }
}

void mergeSort(std::vector<int> &arr) {
    if(arr.size() <= 1)
        return;
    
    std::vector<int>::iterator mid = arr.begin() + (arr.end() - arr.begin()) / 2;
    std::vector<int> lhs_arr(arr.begin(), mid);
    std::vector<int> rhs_arr(mid, arr.end());
    
    mergeSort(lhs_arr);
    mergeSort(rhs_arr);
    merge(lhs_arr.begin(), lhs_arr.end(),
          rhs_arr.begin(), rhs_arr.end(),
          arr.begin()
    );
}


int workingThreads = 0;

void parallelMergeSort(std::vector<int> &arr) {
    if(arr.size() <= 1)
        return;
    
    std::vector<int>::iterator mid = arr.begin() + (arr.end() - arr.begin()) / 2;
    std::vector<int> lhs_arr(arr.begin(), mid);
    std::vector<int> rhs_arr(mid, arr.end());
    
    if(workingThreads <= std::thread::hardware_concurrency()) {
        workingThreads += 2;
        std::thread th1(parallelMergeSort, std::ref(lhs_arr));
        std::thread th2(parallelMergeSort, std::ref(rhs_arr));
        th1.join(); th2.join();
        workingThreads -= 2;
    } else{
        mergeSort(lhs_arr);
        mergeSort(rhs_arr);
    }

    merge(lhs_arr.begin(), lhs_arr.end(),
          rhs_arr.begin(), rhs_arr.end(),
          arr.begin()
    );
}
