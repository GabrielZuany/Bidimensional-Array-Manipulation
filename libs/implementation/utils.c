#include <stdio.h>
#include <stdio.h>
#include "../include/utils.h"

void menu_matrix_convolution(){
    system("make generate");
    Matrix *matrix = matrix_read_binary("generator/matrix_1.bin");
    Matrix *kernel = matrix_read_binary("generator/kernel.bin");
    Matrix *result = matrix_convolution(matrix, kernel);

    printf("Matrix:\n");
    matrix_print_with_null(matrix);

    printf("\n-----\n");
    printf("Kernel (Gauss kernel, blur):\n");
    matrix_print_with_null(kernel);

    printf("\n-----\n");
    printf("Result:\n");
    matrix_print_with_null(result);
    printf("\n");

    matrix_destroy(matrix);
    matrix_destroy(kernel);
    matrix_destroy(result);
}

void menu_matrix_transpose(){
    system("make generate");
    Matrix* matrix_1 = matrix_read_binary("generator/matrix_1.bin");
    Matrix* matrix_1_transpose = matrix_transpose(matrix_1);
    Matrix* matrix_2 = matrix_read_binary("generator/matrix_2.bin");
    Matrix* matrix_2_transpose = matrix_transpose(matrix_2);

    printf("\n-----\n");
    printf("Matrix 1:\n");
    matrix_print_with_null(matrix_1);
    printf("\n-----\n");
    printf("Transpose Matrix 1:\n");
    matrix_print_with_null(matrix_1_transpose);

    printf("\n**********************************\n");
    printf("Matrix 2:\n");
    matrix_print_with_null(matrix_2);
    printf("\n-----\n");
    printf("Transpose Matrix 2:\n");
    matrix_print_with_null(matrix_2_transpose);

    matrix_destroy(matrix_1);
    matrix_destroy(matrix_1_transpose);
    matrix_destroy(matrix_2);
    matrix_destroy(matrix_2_transpose);
}

void menu_matrix_multiplication(){
    system("make generate");
    Matrix* matrix_1 = matrix_read_binary("generator/matrix_1.bin");
    Matrix* matrix_2 = matrix_read_binary("generator/matrix_2.bin");
    Matrix* matrix_1_x_matrix_2 = matrix_multiplication(matrix_1, matrix_2);

    printf("\n-----\n");
    printf("Matrix 1:\n");
    matrix_print_with_null(matrix_1);

    printf("\n-----\n");
    printf("Matrix 2:\n");
    matrix_print_with_null(matrix_2);

    printf("\n-----\n");
    printf("Matrix 1 x Matrix 2:\n");
    matrix_print_with_null(matrix_1_x_matrix_2);

    printf("\n-----\n");

    matrix_destroy(matrix_1);
    matrix_destroy(matrix_2);
    matrix_destroy(matrix_1_x_matrix_2);
}

void menu_matrix_multiplication_by_constant(){
    system("make generate");
    Matrix* matrix_1 = matrix_read_binary("generator/matrix_1.bin");
    double CONSTANT = 4.57;
    Matrix* matrix_1_x_2 = matrix_multiplication_by_value(matrix_1, CONSTANT);

    printf("\n-----\n");
    printf("Matrix 1:\n");
    matrix_print_with_null(matrix_1);

    printf("\n-----\n");
    printf("Constant: %.2lf\n", CONSTANT);

    printf("\n-----\n");
    printf("Matrix 1 x %.2lf:\n", CONSTANT);
    matrix_print_with_null(matrix_1_x_2);

    printf("\n-----\n");

    matrix_destroy(matrix_1);
    matrix_destroy(matrix_1_x_2);
}

void menu_matrix_multiplication_coordinates_by_coordinates(){
    system("make generate");
    Matrix* matrix_1 = matrix_read_binary("generator/matrix_1.bin");
    Matrix* matrix_2 = matrix_read_binary("generator/matrix_2.bin");
    Matrix* matrix_1_x_matrix_2 = matrix_multiplication_by_coordinates(matrix_1, matrix_2);

    printf("\n-----\n");
    printf("Matrix 1:\n");
    matrix_print_with_null(matrix_1);

    printf("\n-----\n");
    printf("Matrix 2:\n");
    matrix_print_with_null(matrix_2);

    printf("\n-----\n");
    printf("Matrix 1 x Matrix 2 (coordinates by coordinates):\n");
    matrix_print_with_null(matrix_1_x_matrix_2);

    printf("\n-----\n");
    matrix_destroy(matrix_1);
    matrix_destroy(matrix_2);
    matrix_destroy(matrix_1_x_matrix_2);
}

void menu_matrix_sum(){
    system("make generate");
    Matrix* matrix_1 = matrix_read_binary("generator/matrix_1.bin");
    Matrix* matrix_2 = matrix_read_binary("generator/matrix_2.bin");
    Matrix* matrix_1_plus_matrix_2 = matrix_sum(matrix_1, matrix_2);

    printf("\n-----\n");
    printf("Matrix 1:\n");
    matrix_print_with_null(matrix_1);

    printf("\n-----\n");
    printf("Matrix 2:\n");
    matrix_print_with_null(matrix_2);

    printf("\n-----\n");
    printf("Matrix 1 + Matrix 2:\n");
    matrix_print_with_null(matrix_1_plus_matrix_2);

    printf("\n-----\n");

    matrix_destroy(matrix_1);
    matrix_destroy(matrix_2);
    matrix_destroy(matrix_1_plus_matrix_2);
}

void menu_matrix_slice(){
    Matrix* matrix = matrix_read_binary("generator/matrix_1.bin");
    int row_start, row_end, column_start, column_end;

    printf("\n-----\n");
    printf("Matrix:\n");
    matrix_print_with_null(matrix);

    printf("Start row: ");
    scanf("%d", &row_start);
    printf("Start column: ");
    scanf("%d", &column_start);

    printf("End row: ");
    scanf("%d", &row_end);
    printf("End column: ");
    scanf("%d", &column_end);

    AxisCoordinates* start = construct_axis_coordinates(row_start, column_start);
    AxisCoordinates* end = construct_axis_coordinates(row_end, column_end);

    Matrix* slice = matrix_slice(matrix, start, end);

    printf("\n-----\n");
    printf("Slice:\n");
    matrix_print_with_null(slice);

    printf("\n-----\n");

    matrix_destroy(matrix);
    matrix_destroy(slice);
    axis_coordinates_destroy(start);
    axis_coordinates_destroy(end);
}

void menu_matrix_get_value_by_coordinates(){
    Matrix* matrix = matrix_read_binary("generator/matrix_1.bin");
    int row, column;
    printf("Row: ");
    scanf("%d", &row);
    printf("Column: ");
    scanf("%d", &column);

    Node* n = matrix_get_node_by_coordinates(matrix, row, column);
    double value = n == NULL ? 0 : node_get_value(n);

    printf("\n-----\n");
    printf("Matrix:\n");
    matrix_print_with_null(matrix);

    printf("\n-----\n");
    printf("(%d,%d) : %.2lf\n", row, column, value);

    printf("\n-----\n");
    matrix_destroy(matrix);
}

void menu_matrix_set_value_by_coordinates(){
    Matrix* matrix = matrix_read_binary("generator/matrix_1.bin");
    int row, column;

    printf("\n-----\n");
    printf("Matrix:\n");
    matrix_print_with_null(matrix);

    printf("Row: ");
    scanf("%d", &row);
    printf("Column: ");
    scanf("%d", &column);

    double value;
    printf("Enter value: ");
    scanf("%lf", &value);

    matrix_insert_element(matrix, row, column, value);

    printf("\n-----\n");
    printf("Matrix:\n");
    matrix_print_with_null(matrix);

    printf("\n-----\n");
    matrix_destroy(matrix);
}

void menu_matrix_swap_rows(){
    Matrix* matrix = matrix_read_binary("generator/matrix_1.bin");
    int row_1, row_2;

    printf("\n-----\n");
    printf("Matrix:\n");
    matrix_print_with_null(matrix);

    printf("Enter row 1: ");
    scanf("%d", &row_1);

    printf("Enter row 2: ");
    scanf("%d", &row_2);

    matrix_swap_rows(matrix, row_1, row_2);

    printf("\n-----\n");
    printf("Matrix:\n");
    matrix_print_with_null(matrix);

    printf("\n-----\n");
    matrix_destroy(matrix);
}


void menu_matrix_swap_columns(){
    Matrix* matrix = matrix_read_binary("generator/matrix_1.bin");
    int column_1, column_2;

    printf("\n-----\n");
    printf("Matrix:\n");
    matrix_print_with_null(matrix);

    printf("Enter column 1: ");
    scanf("%d", &column_1);

    printf("Enter column 2: ");
    scanf("%d", &column_2);

    matrix_swap_columns(matrix, column_1, column_2);

    printf("\n-----\n");
    printf("Matrix:\n");
    matrix_print_with_null(matrix);

    printf("\n-----\n");
    matrix_destroy(matrix);
}
