#include <stdio.h>
#include "../libs/include/list.h"
#include "../libs/include/matrix.h"

void print_double(data_type value){
    printf("%.2lf", value);
}

int main()
{
    int m_r = 9, m_c = 9;

    Matrix *matrix = matrix_construct();

    matrix_set_row_size(matrix, m_r);
    matrix_set_column_size(matrix, m_c);
    matrix_rows_init(matrix, m_r);

    matrix_sequential_fill(matrix);
    matrix_fix_nodes(matrix);

    matrix_print_with_null(matrix);

    matrix_destroy(matrix);
    return 0;
}