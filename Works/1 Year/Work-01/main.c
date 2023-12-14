#include <stdio.h>


size_t findArrayIndex(int *arr, size_t size, int from, int to) {
    size_t i;

    for(i = 0; i < size; i++) {
        if((arr[i] >= from) && (arr[i] <= to)) {
            return i;
        }
    }
    return -1;
}


int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t i= 0 , temp;
    int from = 1, to = 4;

    temp = findArrayIndex(arr, 10, from, to);
    while(temp != -1) {
        i += temp;
        printf("[%d]: %d\n", i, arr[i]);
        i++;
        temp = findArrayIndex(arr + i, 10 - i, from, to);
    }
}