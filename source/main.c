#include <stdio.h>
#include "../libs/include/list.h"
#include "../libs/include/matrix.h"

void print_double(data_type value){
    printf("%.2lf", value);
}

int main()
{
    int n = 3, m = 3;
    double val = 0;

    Matrix *matrix = matrix_construct();
    matrix_set_row_size(matrix, n);
    matrix_set_column_size(matrix, m);
    matrix_rows_init(matrix, n);
    matrix_columns_init(matrix, m);

    data_type values[n*m];

    for(int i = 0; i < n*m; i++){
        values[i] = val;
        val++;
    }

    matrix_fill_zeros(matrix);
    matrix_fix_nodes(matrix);

    matrix_print_rows(matrix, print_double);

    printf("\n---\n");

    matrix_replace_element(matrix, 1, 1, 10);
    matrix_replace_element(matrix, 1, 2, 20);
    matrix_replace_element(matrix, 2, 1, 30);
    matrix_replace_element(matrix, 1, 0, 40);
    matrix_replace_element(matrix, 0, 1, 50);

    matrix_print_columns(matrix, print_double);

    //get node by coordinates
    Node *node = matrix_get_node_by_coordinates(matrix, 1, 1);
    printf("\nNode value: %.2lf\n", node_get_value(node));
    printf("Node above value: %.2lf\n", node_get_value(node_get_column_previous(node)));
    printf("Node below value: %.2lf\n", node_get_value(node_get_column_next(node)));
    printf("Node left value: %.2lf\n", node_get_value(node_get_row_previous(node)));
    printf("Node right value: %.2lf\n", node_get_value(node_get_row_next(node)));


    matrix_destroy(matrix);

    return 0;
}