#ifndef _MATRIX_H
#define _MATRIX_H

#include "list.h"
#include "node.h"

typedef struct Matrix Matrix;

Matrix *matrix_construct();

void matrix_print_rows(Matrix *m, void (*fptr_print_fn)(data_type));

void matrix_print_columns(Matrix *m, void (*fptr_print_fn)(data_type));

void matrix_rows_init(Matrix *m, int size);

void matrix_columns_init(Matrix *m, int size);

void matrix_set_row_size(Matrix *m, int size);

void matrix_set_column_size(Matrix *m, int size);

int matrix_get_row_size(Matrix *m);

int matrix_get_column_size(Matrix *m);

List *matrix_get_full_row(Matrix *m, int row);

List *matrix_get_full_column(Matrix *m, int column);

Node *matrix_get_node_by_coordinates(Matrix *m, int row, int column);

void matrix_replace_element(Matrix* m, int row, int column, data_type value);

void matrix_fill(Matrix *m, data_type *values);

void matrix_fill_zeros(Matrix *m);

void matrix_fix_nodes(Matrix *m);

void matrix_print(Matrix *m);

Matrix *matrix_sum(Matrix* m1, Matrix* m2);

Matrix *matrix_multiplication_by_coordinates(Matrix* m1, Matrix* m2);

Matrix *matrix_multiplication_by_value(Matrix* m1, data_type value);

Matrix *matrix_multiplication(Matrix *m1, Matrix *m2);

void matrix_destroy(Matrix *m);

#endif 