#include <stdio.h>
#include "../libs/include/list.h"
#include "../libs/include/matrix.h"

void print_double(data_type value){
    if(value == null){
        printf("null");
    }
    printf("%.2lf", value);
}

int main()
{
    int n = 3, m = 3;
    double val = 0;

    Matrix *matrix = matrix_construct();
    Matrix *matrix2 = matrix_construct();

    matrix_set_row_size(matrix, n);
    matrix_set_column_size(matrix, m);
    matrix_rows_init(matrix, n);
    matrix_columns_init(matrix, m);

    matrix_set_row_size(matrix2, n);
    matrix_set_column_size(matrix2, m);
    matrix_rows_init(matrix2, n);
    matrix_columns_init(matrix2, m);

    data_type values[9] = {0,0,10,2,3,0,3,8,0};
    data_type values2[9] = {1,1,10,2,0,0,0,8,0};

    matrix_fill(matrix, values);
    matrix_fix_nodes(matrix);

    matrix_fill(matrix2, values2);
    matrix_fix_nodes(matrix2);


    matrix_print(matrix);
    printf("\n---\n");

    matrix_print(matrix2);
    printf("\n---\n");

    Matrix *matrix3 = matrix_multiplication(matrix, matrix2);
    matrix_print(matrix3);
    printf("\n---\n");

    matrix_destroy(matrix);
    matrix_destroy(matrix2);
    matrix_destroy(matrix3);
    return 0;
}