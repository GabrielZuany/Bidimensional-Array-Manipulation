#include <stdio.h>
#include "../libs/include/list.h"
#include "../libs/include/matrix.h"

void print_double(data_type value){
    printf("%.2lf", value);
}

int main()
{
    int n = 2, m = 2;
    double val = 0;

    Matrix *matrix = matrix_construct();
    matrix_set_row_size(matrix, n);
    matrix_set_column_size(matrix, m);
    matrix_rows_init(matrix, n);
    matrix_columns_init(matrix, m);

    //fill matrix
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            matrix_insert_element(matrix, i, j, val);
            val++;
        }
    }
    //print matrix
    matrix_print_rows(matrix, print_double);

    printf("\n\n");

    Matrix *matrix2 = matrix_construct();
    matrix_set_row_size(matrix2, n);
    matrix_set_column_size(matrix2, m);
    matrix_rows_init(matrix2, n);
    matrix_columns_init(matrix2, m);

    //fill matrix
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            matrix_insert_element(matrix2, i, j, val);
            val++;
        }
    }

    matrix_print_rows(matrix2, print_double);
    

    matrix_destroy(matrix);

    return 0;
}