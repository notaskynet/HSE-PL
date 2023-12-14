#include "functions.h"

#define MAX(num1, num2) ((num1) > (num2)) ? (num1) : (num2)
#define MIN(num1, num2) ((num1) < (num2)) ? (num1) : (num2)


void get_choice(int *choice, const char **options, int options_size) {
    printf("Chose what you want to do with your table:\n");
    print_options(options, options_size);
    do {
        get_int(choice);
        if(((*choice) < 1) && ((*choice) > options_size)) {
            printf("You can enter a number from 1 to %d!\n", options_size);
        }
    } while(((*choice) < 1) && ((*choice) > options_size));
}


void menu(table *p_data) {
    const char *options[5] = {"1. Print table" ,
                              "2. Change cell value",
                              "3. Search values",
                              "4. Change number of rows",
                              "5. Exit" };
    unsigned long col, row;
    double from, to;
    int choice, flag;

    flag = 1;
    do {
        get_choice(&choice, options, 5);
        switch(choice) {
            case 1: {
                print_table(p_data);
                break;
            } case 2: {
                printf("Enter the number of the column and row you want to change\nCol:\n");
                get_ulong(&col);
                printf("Row:\n");
                get_ulong(&row);
                set_cell(p_data, row, col);
                break;
            } case 3: {
                printf("Enter the range:\n");
                get_double(&from);
                get_double(&to);
                search_values(p_data, MIN(to, from), MAX(to, from));
                break;
            } case 4: {
                printf("How many rows do you want to print?\n");
                set_row(p_data);
                break;
            } case 5: {
                flag = 0;
                break;
            }
        }
    } while(flag);
}


int main() {
    table data;

    init_table(&data);
    menu(&data);

    return 0;
}


