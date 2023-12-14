#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    unsigned int rows;

    unsigned long col1[20];
    int col2[20];
    double col3[20];
} table;



void clean_buffer();
void get_ulong(unsigned long *);
void get_double(double *);
void get_int(int *);
int calculate_ulong_width(unsigned long);
int calculate_dwidth(double);
int calculate_iwidth(int);
void print_options(const char **, size_t);


void init_table(table *p_data);
void set_cell(table *, int, int);
void set_row(table *);
void search_values(table *, double,  double);
void print_table(table *);
