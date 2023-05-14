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

void matrix_update_column_head(Matrix *m, int index, Node *head){
    list_set_head(m->columns[index], head);
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

Node *matrix_get_node_by_coordinates(Matrix *m, int row, int column){
    List *list = m->rows[row];
    Node *node = list_get_head(list);
    while(node != NULL){
        AxisCoordinates *axis_coordinates = node_get_coordinates(node);
        if(axis_coordenates_get_y(axis_coordinates) == column){
            return node;
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
            if(v == 0){
                continue;
            }
            list_push_back(m->rows[i], v, construct_axis_coordinates(i, j));
        }
    }
}

//fill the matrix
void matrix_fill(Matrix *m, data_type *values){
    int index = 0;
    for(int i = 0; i < m->rows_size; i++){
        for(int j = 0; j < m->columns_size; j++){
            if(values[index] == 0){
                index++;
                continue;
            }
            list_push_back(m->rows[i], values[index], construct_axis_coordinates(i, j));
            index++;
        }
    }
}

void matrix_fix_nodes(Matrix *m){
    int row = 0, column = 0;

    for(int i = 0; i < m->rows_size; i++){
        List *list = m->rows[i];
        List *next_list = list;
        List *previous_list = list;

        if(i+1 < m->rows_size){
            next_list = m->rows[i + 1];
        }

        if(i != 0){
            previous_list = m->rows[i - 1];
        }

        Node *node = list_get_head(list);
        Node *below_next_node = list_get_head(next_list);
        Node *above_previous_node = list_get_head(previous_list);

        while(column < m->columns_size && node != NULL){
            AxisCoordinates *axis_coordinates = node_get_coordinates(node);
            row = axis_coordenates_get_x(axis_coordinates);
            column = axis_coordenates_get_y(axis_coordinates);
            
            // fix the matrix edges (columns nodes)
            if(row == 0){
                node_set_column_previous(node, NULL);
                node_set_column_next(node, below_next_node);
            }else if(row == m->rows_size - 1){
                node_set_column_previous(node, above_previous_node);
                node_set_column_next(node, NULL);
            }else{
                node_set_column_previous(node, above_previous_node);
                node_set_column_next(node, below_next_node);
            }
            
            // fix the matrix edges (rows nodes)
            if(column == 0){
                node_set_row_previous(node, NULL);
            }else if(column == m->columns_size - 1){
                node_set_row_next(node, NULL);
            }else{
                node_set_row_next(node, node_get_row_next(node));
            }

            node = node_get_row_next(node);
            if(node == NULL){
                break;
            }
            above_previous_node = node_get_row_next(above_previous_node);
            below_next_node = node_get_row_next(below_next_node);
        }
        m->rows[i] = list;
    }
}

void matrix_replace_element(Matrix* m, int row, int column, data_type value){
    Node* n = matrix_get_node_by_coordinates(m, row, column);
    if(n==NULL){
        printf("Node not found, creating new node\n");
        AxisCoordinates *axis_coordinates = construct_axis_coordinates(row, column);
        n = node_construct(value, NULL, NULL, NULL, NULL, axis_coordinates);
        list_push_back(m->rows[row], value, axis_coordinates);
        matrix_fix_nodes(m);
    }else{
        node_set_value(n, value);
    }
}

void matrix_print_rows(Matrix *m, void (*fptr_print_fn)(data_type)){
    for(int i = 0; i < m->rows_size; i++){
        list_print(m->rows[i], fptr_print_fn);
    }
}

void matrix_print_columns(Matrix *m, void (*fptr_print_fn)(data_type)){
    for(int i = 0; i < m->columns_size; i++){
        list_print(m->columns[i], fptr_print_fn);
    }
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