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

Node *matrix_get_node_by_coordinates(Matrix *m, int row, int column){
    List *list = m->rows[row];
    Node *node = list_get_head(list);
    while(node != NULL){
        AxisCoordinates *axis_coordinates = node_get_coordinates(node);
        if(axis_coordenates_get_y(axis_coordinates) == column){
            return node;
        }
        if(node_get_row_next(node) == NULL){
            break;
        }
        node = node_get_row_next(node);
    }
    return NULL;
}

void matrix_print(Matrix *m){
    int i = 0, j = 0;
    for(i = 0; i < m->rows_size; i++){
        printf("[");
        for(j = 0; j < m->columns_size; j++){
            Node *node = matrix_get_node_by_coordinates(m, i, j);
            if(node == NULL){
                printf("NULL, ");
            }else{
                printf("%.2lf, ", node_get_value(node));
            }
        }
        printf("]");
        printf("\n");
    }
}

//fill with zeros
void matrix_fill_zeros(Matrix *m){
    int v = 0;
    for(int i = 0; i < m->rows_size; i++){
        for(int j = 0; j < m->columns_size; j++){
            list_push_back(m->rows[i], v, construct_axis_coordinates(i, j));
        }
    }
}

//fill the matrix
void matrix_fill(Matrix *m, data_type *values){
    int index = 0;
    for(int i = 0; i < m->rows_size; i++){
        for(int j = 0; j < m->columns_size; j++){
            if(values[index] == 0 || values[index] == null){
                index++;
                continue;
            }
            list_push_back(m->rows[i], values[index], construct_axis_coordinates(i, j));
            index++;
        }
    }
}

Node* matrix_get_column_next_valid_node(Matrix* m, int row_index, int column_index){
    for(int i = row_index + 1; i < m->rows_size; i++){
        Node* node = matrix_get_node_by_coordinates(m, i, column_index);
        if(node != NULL){
            return node;
        }
    }
    return NULL;
}

Node* matrix_get_column_previous_valid_node(Matrix* m, int row_index, int column_index){
    for(int i = row_index - 1; i >= 0; i--){
        Node* node = matrix_get_node_by_coordinates(m, i, column_index);
        if(node != NULL){
            return node;
        }
    }
    return NULL;
}

Node* matrix_get_row_next_valid_node(Matrix* m, int row_index, int column_index){
    for(int i = column_index + 1; i < m->columns_size; i++){
        Node* node = matrix_get_node_by_coordinates(m, row_index, i);
        if(node != NULL){
            return node;
        }
    }
    return NULL;
}

Node* matrix_get_row_previous_valid_node(Matrix* m, int row_index, int column_index){
    for(int i = column_index - 1; i >= 0; i--){
        Node* node = matrix_get_node_by_coordinates(m, row_index, i);
        if(node != NULL){
            return node;
        }
    }
    return NULL;
}

void matrix_fix_nodes(Matrix *m){
    int row = 0, column = 0;
    for(int i = 0; i < m->rows_size; i++){
        for(int j = 0; j < m->columns_size; j++){
            Node* node = matrix_get_node_by_coordinates(m, i, j);
            if(node == NULL){
                continue;
            }
            Node* row_next = matrix_get_row_next_valid_node(m, i, j);
            Node* row_prev = matrix_get_row_previous_valid_node(m, i, j);
            Node* column_next = matrix_get_column_next_valid_node(m, i, j);
            Node* column_prev = matrix_get_column_previous_valid_node(m, i, j);
            node_set_row_next(node, row_next);
            node_set_row_previous(node, row_prev);
            node_set_column_next(node, column_next);
            node_set_column_previous(node, column_prev);
        }
    }
}

void matrix_print_rows(Matrix *m, void (*fptr_print_fn)(data_type)){
    for(int i = 0; i < m->rows_size; i++){
        list_print(m->rows[i], fptr_print_fn);
    }
}

Matrix *matrix_sum(Matrix* m1, Matrix* m2){
    Matrix *m = matrix_construct(m1->rows_size, m1->columns_size);
    matrix_set_row_size(m, m1->rows_size);
    matrix_set_column_size(m, m1->columns_size);
    matrix_rows_init(m, m1->rows_size);
    matrix_columns_init(m, m1->columns_size);
    Node *n1 = NULL;
    Node *n2 = NULL;
    int count = 0;
    data_type values[m1->rows_size*m1->columns_size];

    for(int i = 0; i < m1->rows_size; i++){
        for(int j = 0; j < m1->columns_size; j++){
            n1 = matrix_get_node_by_coordinates(m1, i, j);
            n2 = matrix_get_node_by_coordinates(m2, i, j);
            if(n1 == NULL){
                values[count] = node_get_value(n2);
            }else if(n2 == NULL){
                values[count] = node_get_value(n1);
            }else if(n1 != NULL && n2 != NULL){
                values[count] = node_get_value(n1) + node_get_value(n2);
            }else if(n1 == NULL && n2 == NULL){
                values[count] = 0;
            }
            count++;
        }
    }
    matrix_fill(m, values);
    matrix_fix_nodes(m);
    return m;
}

Matrix *matrix_multiplication_by_coordinates(Matrix* m1, Matrix* m2){
    Matrix *m = matrix_construct(m1->rows_size, m1->columns_size);
    matrix_set_row_size(m, m1->rows_size);
    matrix_set_column_size(m, m1->columns_size);
    matrix_rows_init(m, m1->rows_size);
    matrix_columns_init(m, m1->columns_size);
    Node *n1 = NULL;
    Node *n2 = NULL;
    int count = 0;
    data_type values[m1->rows_size*m1->columns_size];

    for(int i = 0; i < m1->rows_size; i++){
        for(int j = 0; j < m1->columns_size; j++){
            n1 = matrix_get_node_by_coordinates(m1, i, j);
            n2 = matrix_get_node_by_coordinates(m2, i, j);
            if(n1 == NULL || n2 == NULL){
                values[count] = 0;
            }else if(n1 != NULL && n2 != NULL){
                values[count] = node_get_value(n1) * node_get_value(n2);
            }
            count++;
        }
    }
    matrix_fill(m, values);
    matrix_fix_nodes(m);
    return m;
}

Matrix *matrix_multiplication_by_value(Matrix* m1, data_type value){
    Matrix *m = matrix_construct(m1->rows_size, m1->columns_size);
    matrix_set_row_size(m, m1->rows_size);
    matrix_set_column_size(m, m1->columns_size);
    matrix_rows_init(m, m1->rows_size);
    matrix_columns_init(m, m1->columns_size);
    Node *n1 = NULL;
    int count = 0;
    data_type values[m1->rows_size*m1->columns_size];

    for(int i = 0; i < m1->rows_size; i++){
        for(int j = 0; j < m1->columns_size; j++){
            n1 = matrix_get_node_by_coordinates(m1, i, j);
            if(n1 == NULL){
                values[count] = 0;
            }else if(n1 != NULL){
                values[count] = node_get_value(n1) * value;
            }
            count++;
        }
    }
    matrix_fill(m, values);
    matrix_fix_nodes(m);
    return m;
}

Matrix *matrix_multiplication(Matrix *m1, Matrix *m2){
    if(m1->columns_size != m2->rows_size){
        printf("Error: matrix_multiplication: rows of matrix 1 must be same size of matrix 2 columns\n");
        return NULL;
    }

    Matrix *m = matrix_construct(m1->rows_size, m2->columns_size);
    matrix_set_row_size(m, m1->rows_size);
    matrix_set_column_size(m, m2->columns_size);
    matrix_rows_init(m, m1->rows_size);
    matrix_columns_init(m, m2->columns_size);
    Node *n1 = NULL;
    Node *n2 = NULL;
    int m1_row_index = 0, m1_column_index = 0, m2_row_index = 0, m2_column_index = 0;
    data_type sum = 0;
    data_type values[m1->rows_size*m2->columns_size];

    for(m1_row_index = 0; m1_row_index < m1->rows_size; m1_row_index++){
        for(m2_column_index = 0; m2_column_index < m2->columns_size; m2_column_index++){
            sum = 0;
            for(m1_column_index = 0, m2_row_index = 0; m1_column_index < m1->columns_size; m1_column_index++, m2_row_index++){
                n1 = matrix_get_node_by_coordinates(m1, m1_row_index, m1_column_index);
                n2 = matrix_get_node_by_coordinates(m2, m2_row_index, m2_column_index);
                if(n1 != NULL && n2 != NULL){
                    sum += node_get_value(n1) * node_get_value(n2);
                }
            }
            values[m1_row_index*m2->columns_size + m2_column_index] = sum;
        }
    }
    matrix_fill(m, values);
    matrix_fix_nodes(m);
    return m;
}

void matrix_swap_rows(Matrix *m, int row1, int row2){
    List* r1 = m->rows[row1];
    List* r2 = m->rows[row2];
    m->rows[row1] = r2;
    m->rows[row2] = r1;
    matrix_fix_nodes(m);
}

void matrix_insert_element(Matrix *m, int row, int column, data_type value){
    Node *n = matrix_get_node_by_coordinates(m, row, column);
    if(n != NULL){
        node_set_value(n, value);
        return;
    }
    n = node_construct(value, NULL, NULL, NULL, NULL, construct_axis_coordinates(row, column));
    list_insert(m->rows[row], n, column);
    matrix_fix_nodes(m);
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