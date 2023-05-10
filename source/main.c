#include <stdio.h>
#include "../libs/include/list.h"
#include "../libs/include/matrix.h"

int main()
{
    int n = 2, m = 2;
    double val = 1;

    Matrix *matrix = matrix_construct();
    matrix_set_row_size(matrix, n);
    matrix_set_column_size(matrix, m);
    matrix_rows_init(matrix, n);
    matrix_columns_init(matrix, m);

    //fill matrix
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            
        }
    }
    

    matrix_destroy(matrix);

    return 0;
}