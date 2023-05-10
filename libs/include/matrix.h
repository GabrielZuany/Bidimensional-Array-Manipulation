#ifndef _MATRIX_H
#define _MATRIX_H

#include "list.h"
#include "node.h"

typedef struct Matrix Matrix;

Matrix *matrix_construct();

void matrix_rows_init(Matrix *m, int size);

void matrix_columns_init(Matrix *m, int size);

void matrix_set_row_size(Matrix *m, int size);

void matrix_set_column_size(Matrix *m, int size);

int matrix_get_row_size(Matrix *m);

int matrix_get_column_size(Matrix *m);

List *matrix_get_full_row(Matrix *m, int row);

List *matrix_get_full_column(Matrix *m, int column);

void insert_into_row(Matrix *m, int row, int column, data_type value);

void insert_into_column(Matrix *m, int row, int column, data_type value);

void matrix_destroy(Matrix *m);

#endif 