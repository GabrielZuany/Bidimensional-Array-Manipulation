#include <stdlib.h>
#include <stdio.h>
#include "../include/matrix.h"
#include "../include/list.h"
#include "../include/node.h"
#include "../include/axis_coordinates.h"

struct Matrix
{
    List **rows;
    List **columns;
    int rows_size;
    int columns_size;
};

Matrix *matrix_construct(){
    Matrix *m = (Matrix *)malloc(sizeof(Matrix));
    m->rows = NULL;
    m->columns = NULL;
    m->rows_size = 0;
    m->columns_size = 0;
    return m;
}

void matrix_rows_init(Matrix *m, int size){
    m->rows = (List **)malloc(sizeof(List *) * size);
    for(int i = 0; i < size; i++){
        m->rows[i] = list_construct();
    }
}

void matrix_columns_init(Matrix *m, int size){
    m->columns = (List **)malloc(sizeof(List *) * size);
    for(int i = 0; i < size; i++){
        m->columns[i] = list_construct();
    }
}

void matrix_set_row_size(Matrix *m, int size){
    m->rows_size = size;
}

void matrix_set_column_size(Matrix *m, int size){
    m->columns_size = size;
}

int matrix_get_row_size(Matrix *m){
    return m->rows_size;
}

int matrix_get_column_size(Matrix *m){
    return m->columns_size;
}

List *matrix_get_full_row(Matrix *m, int row){
    return m->rows[row];
}

List *matrix_get_full_column(Matrix *m, int column){
    return m->columns[column];
}

void insert_into_row(Matrix *m, int row, int column, data_type value){
    list_push_back(m->rows[row], value, construct_axis_coordinates(row, column));
}

void insert_into_column(Matrix *m, int row, int column, data_type value){
    list_push_back(m->columns[column], value, construct_axis_coordinates(row, column));
}

void matrix_destroy(Matrix *m){
    for(int i = 0; i < m->rows_size; i++){
        list_destroy(m->rows[i]);
    }
    for(int i = 0; i < m->columns_size; i++){
        list_destroy(m->columns[i]);
    }
    free(m->rows);
    free(m->columns);
    free(m);
}