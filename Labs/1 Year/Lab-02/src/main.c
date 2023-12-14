#include <malloc.h>
#include <stdio.h>

#define FALSE 0
#define TRUE  1

#define CLEAN_BUFFER() { int ch; while ((ch = getchar()) != EOF && ch != '\n') {} }


void get_value(int *value) {
    int input_size;

    do {
        input_size = scanf("%d", value);
        CLEAN_BUFFER()
        
        if(input_size < 0) {
            printf("Error! Try enter another value:\n");
        }
        else if (input_size != 1) {
            printf("Incorrect value! Try enter another one:\n");
        }
    } while(1 != input_size);
}


void array_input(int *arr, size_t arr_size) {
    size_t i;

    printf("Enter the value of the array elements\n");
    for(i = 0; i < arr_size; i++) {
        printf(">> %lld\n", i);
        get_value(arr + i);
    }
}


int main() {
    int arr_size;
    int *arr = NULL;

    printf("Enter size of array:\n");
    get_value(&arr_size);
    arr = (int *) malloc(arr_size * sizeof(int));
    array_input(arr, arr_size);
    free(arr);

    return 0;
}