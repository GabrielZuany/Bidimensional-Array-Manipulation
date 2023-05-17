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

    Matrix *matrix2 = matrix_construct();

    matrix_set_row_size(matrix2, n);
    matrix_set_column_size(matrix2, m);
    matrix_rows_init(matrix2, n);
    matrix_columns_init(matrix2, m);
   
    data_type values2[9] = {1,2,3,4,0,6,7,8,9};

    matrix_fill(matrix2, values2);
    matrix_fix_nodes(matrix2);

    matrix_print(matrix2);
    printf("\n---\n");

    //matrix_swap_rows(matrix2, 0, 1);
    matrix_insert_element(matrix2, 1, 1, 50);
    matrix_print(matrix2);
    Node *node = matrix_get_node_by_coordinates(matrix2, 1, 0);
    printf("node: %.2lf\n", node_get_value(node));
    printf("row_next: %.2lf\n", node_get_value(node_get_row_next(node)));
    printf("row_prev: %.2lf\n", node_get_value(node_get_row_previous(node)));
    printf("col_next: %.2lf\n", node_get_value(node_get_column_next(node)));
    printf("col_prev: %.2lf\n", node_get_value(node_get_column_previous(node)));

    
    printf("\n---\n");

   
    matrix_destroy(matrix2);

    return 0;
}