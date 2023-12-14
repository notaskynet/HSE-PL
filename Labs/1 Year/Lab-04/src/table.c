#include "functions.h"


void clean_buffer() {
    int ch;

    while ((ch = getchar()) && (ch != EOF) && (ch != '\n')) {}
}


void get_ulong(unsigned long *p_val) {
    int check_error;

    do {
        check_error = scanf("%lu", p_val);
        if (check_error < 1) {
            printf("Error! Try again.\n");
        } else if (check_error > 1){
            printf("Incorrect value! Try again.\n");
        }
        clean_buffer();
    } while(check_error != 1);
    
}


void get_double(double *p_val) {
    int check_error;

    do {
        check_error = scanf("%lf", p_val);
        if (check_error < 1) {
            printf("Error! Try again.\n");
        } else if (check_error > 1){
            printf("Incorrect value! Try again.\n");
        }
        clean_buffer();
    } while(check_error != 1);
}


void get_int(int *p_val) {
    int check_error;

    do {
        check_error = scanf("%d", p_val);
        if (check_error < 1) {
            printf("Error! Try again.\n");
        } else if (check_error > 1){
            printf("Incorrect value! Try again.\n");
        }
        clean_buffer();
    } while(check_error != 1);
}


int calculate_iwidth(int num) {
    char buf[64];

    sprintf(buf, "%d", num);
    return strlen(buf);
}


int calculate_ulong_width(unsigned long num) {
    char buf[64];

    sprintf(buf, "%lu", num);
    return strlen(buf);
}


int calculate_dwidth(double num) {
    char buf[64];

    sprintf(buf, "%f", num);
    return strlen(buf);
}


void print_options(const char **options, size_t options_size) {
    size_t i;

    for(i = 0; i < options_size; i++) {
        printf("%s\n", options[i]);
    }
}

void set_cell(table *p_data, int row, int col) {
    printf("[%d][%d]: ", row, col);
    if(col == 1) get_ulong((*p_data).col1 + (row - 1));
    if(col == 2) get_int((*p_data).col2 + (row - 1));
    if(col == 3) get_double((*p_data).col3 + (row - 1));
}


void set_table(table *p_data) {
    size_t i, j;

    for (i = 1; i <= (*p_data).rows; i++) {
        for (j = 1; j <= 3; j++) {
            set_cell(p_data, i, j);
        }
    }
}


void set_row(table *p_data) {
    unsigned long set_row;
    size_t i;

    do {
        get_ulong(&set_row);
        if((set_row > 20) || (set_row < 1)) {
            printf("Incorrect value. Try again!");
        }
    } while((set_row > 20) || (set_row < 1));
    (*p_data).rows = set_row;
    for(i = (*p_data).rows - 1; i < 20; i++) {
        (*p_data).col1[i] = 0;
        (*p_data).col2[i] = 0;
        (*p_data).col3[i] = 0.0f;
    }
}


void init_table(table *p_data) {
    int choice;
    size_t i;

    (*p_data).rows = 20;
    printf("Hi! Do you want to init a table with custom values?\n(Type 1 if you want to do it and 0 if you don`t want to do it)\n");
    do {
        get_int(&choice);
        if(choice != 1 && choice != 0) {
            printf("Inccorrect value! Try again\n");
        }
    } while(choice != 1 && choice != 0);
    if(choice) {
        set_table(p_data);
    } else {
        for(i = 0; i < (*p_data).rows; i++) {
            (*p_data).col1[i] = 0;
            (*p_data).col2[i] = 0;
            (*p_data).col3[i] = 0.0f;
        }
    }
}


int get_table_width(table *p_data) {
    int width1, width2, width3, max_width;
    size_t i;

    max_width = -1;
    for(i = 0; i < (*p_data).rows; i++) {
        width1 = calculate_ulong_width((*p_data).col1[i]);
        width2 = calculate_iwidth((*p_data).col2[i]);
        width3 = calculate_dwidth((*p_data).col3[i]);
        max_width = MAX(MAX(width1, width2), MAX(width3, max_width));
    }
    return max_width;
}


char *get_separator(size_t width) {
    char *separator;
    size_t i, size;
    
    size = 3 * (width + 2) + 3;
    separator = (char *) malloc(size * sizeof(char));
    if(separator == NULL) {
        printf("Memory leak!\n");
        exit(-1);
    }
    for(i = 0; i < size - 1; i++) {
        separator[i] = '-';
    }
    separator[size - 1] = '\0';

    return separator;
}


int check_diaposon(table *p_data, size_t row, double from, double to) {
    double temp1 = (double) (*p_data).col1[row];
    double temp2 = (double) (*p_data).col2[row];
    double temp3 = (*p_data).col3[row];

    if( ( MAX(temp1, MAX( temp2, temp3 )) <= to ) &&
        ( MIN(temp1, MIN( temp2, temp3 )) >= from )) {
        return 1;
    } return 0;
}


void search_values(table *p_data, double from,  double to) {
    int width = get_table_width(p_data);
    char format_line[64];
    char *separator;
    size_t i;

    separator = get_separator(width);
    sprintf(format_line, "| %%%dlu | %%%dd | %%%df |\n", width, width, width);
    printf("+%s+\n", separator);
    for(i = 0; i < (*p_data).rows; i++) {
                if(check_diaposon(p_data, i, from, to)) {
            printf(format_line, (*p_data).col1[i], (*p_data).col2[i], (*p_data).col3[i]);
            printf("+%s+\n", separator);
        }
    }
    free(separator);
}


void print_table(table *p_data) {
    int width = get_table_width(p_data);
    char format_line[64];
    char *separator;
    size_t i;

    separator = get_separator(width);
    sprintf(format_line, "| %%%dlu | %%%dd | %%%df |\n", width, width, width);
    printf("+%s+\n", separator);
    for(i = 0; i < (*p_data).rows; i++) {
        printf(format_line, (*p_data).col1[i], (*p_data).col2[i], (*p_data).col3[i]);
        printf("+%s+\n", separator);
    }
    free(separator);
}
