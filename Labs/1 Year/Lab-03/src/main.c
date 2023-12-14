#include <stdlib.h>
#include <stdio.h>


int calculateNumWidth(int num) {
    int width = 0;

    while(num != 0) {
        num /= 10;
        width++;
    }
    return width;
}


int calculateMaxWidth(const int *arr, size_t arr_size) {
    int max_num, tmp;
    size_t i;

    if(arr == NULL) {
        return 0;
    }
    else {
        max_num = 0;
        for(i = 0; i < arr_size; i++) {
            tmp = (arr[i] < 0) ? (-10 * arr[i]) : (arr[i]); // Сравниваем по длине
            if(max_num < tmp) {
                max_num = tmp;
            }
        }
    }
    return calculateNumWidth(max_num);
}


void formatArrayLine(char *line, size_t width, char fill_symbol) {
    size_t i;

    line[width] = '\0';
    for(i = 0; i < width; i++) {
        line[i] = fill_symbol;
    }
}


void printArr(int *arr, size_t arr_size) {
    char value_format[32] = {'\0'};
    char *next_line;

    int width;
    size_t i;

    width = calculateWidth(arr, arr_size);
    next_line = (char*) malloc((width + 3) * sizeof(char));

    formatArrayLine(next_line, width + 2, '-');
    sprintf(value_format, "| %%%dd |\n", width);
    printf("+%s+\n", next_line);
    for(i = 0; i < arr_size; i++) {
        printf(value_format, arr[i]);
        printf("+%s+\n", next_line);
    }
    free(next_line);
}


int main() {
    int arr[] = {1323, -2122, 232323, 2121214, -2121214};
    printArr(arr, 5);

    return 0;
}
