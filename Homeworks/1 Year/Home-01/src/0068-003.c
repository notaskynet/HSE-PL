#include <stdlib.h>
#include <stdio.h>
#include <math.h>


void getValue(char format[], int *valueAdd) {
    int err_check;

    err_check = scanf(format, valueAdd);
    if(1 != err_check) {
        exit(1);
    }
}


void fill_arr(int *arr, size_t arr_size) {
    size_t i;

    for(i = 0; i < arr_size; i++) {
        arr[i] = 0;
    }
}


int checkNoEquelNums(int *arr, size_t arr_size, int n) {
    size_t i;

    for(i = 0; n != 0; i++) {
        arr[n % 10]++;
        n /= 10;
    }

    for(i = 0; i < arr_size; i++) {
        if(arr[i] > 1) {
            return 0;
        }
    }
    return 1;
}


int main() {
    int nums[10];
    int n;

    getValue("%d", &n);
    fill_arr(nums, 10);
    if(checkEquel(nums, 10, n)) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }

    return 0;
}