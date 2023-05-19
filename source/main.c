#include <stdio.h>
#include "../libs/include/list.h"
#include "../libs/include/matrix.h"

void print_double(data_type value){
    printf("%.2lf", value);
}

int main()
{
    int m_r = 9, m_c = 9;
    int k_r = 3, k_c = 3;

    Matrix *matrix = matrix_construct();
    Matrix *kernel = matrix_construct();

    matrix_set_row_size(matrix, m_r);
    matrix_set_column_size(matrix, m_c);
    matrix_rows_init(matrix, m_r);

    matrix_set_row_size(kernel, k_r);
    matrix_set_column_size(kernel, k_c);
    matrix_rows_init(kernel, k_r);

    matrix_sequential_fill(matrix);
    matrix_fix_nodes(matrix);

    matrix_sequential_fill(kernel);
    matrix_fix_nodes(kernel);

    matrix_print(matrix);
    Matrix *convolution_result = matrix_convolution(matrix, kernel);
    matrix_print(convolution_result);

    matrix_destroy(matrix);
    matrix_destroy(kernel);
    matrix_destroy(convolution_result);
    return 0;
}