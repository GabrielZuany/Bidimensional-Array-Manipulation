#include <stdlib.h>
#include <stdio.h>
#include "../include/matrix.h"
#include "../include/list.h"
#include "../include/node.h"
#include "../include/axis_coordinates.h"
#include <math.h>
#include <string.h>

struct Matrix
{
    List **rows;
    int rows_size;
    int columns_size;
};

void matrix_save_binary(Matrix *m, char *filename){
    FILE *file = fopen(filename, "wb");
    fwrite(&m->rows_size, sizeof(int), 1, file);
    fwrite(&m->columns_size, sizeof(int), 1, file);
    
    for(int i = 0; i < m->rows_size; i++){
        for(int j = 0; j < m->columns_size; j++){
            Node *node = matrix_get_node_by_coordinates(m, i, j);
            if(node != NULL){
                data_type value = node_get_value(node);
                fwrite(&value, sizeof(data_type), 1, file);
            }else{
                char empty[] = "null";
                fwrite(empty, sizeof(char), 4, file);
            }
        }
    }
    fclose(file);
}

Matrix *matrix_read_binary(char *filename){
    FILE *file = fopen(filename, "rb");
    Matrix *m = matrix_construct();
    fread(&m->rows_size, sizeof(int), 1, file);
    fread(&m->columns_size, sizeof(int), 1, file);
    matrix_rows_init(m, m->rows_size);
    data_type values[m->rows_size * m->columns_size];
    int index = 0;
    for(int i = 0; i < m->rows_size; i++){
        for(int j = 0; j < m->columns_size; j++){
            char empty[5];
            fread(empty, sizeof(char), 4, file);
            empty[4] = '\0';
            if(strcmp(empty, "null") == 0){
                values[index] = 0;
            }else{
                fseek(file, -4, SEEK_CUR);
                fread(&values[index], sizeof(data_type), 1, file);
            }
            index++;
        }
    }
    matrix_fill(m, values);
    matrix_fix_nodes(m);
    fclose(file);
    return m;
}

Matrix *matrix_construct(){
    Matrix *m = (Matrix *)malloc(sizeof(Matrix));
    m->rows = NULL;
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
    if(row < 0 || column < 0 || row >= m->rows_size || column >= m->columns_size){
        return NULL;
    }
    List *list = m->rows[row];
    Node *node = list_get_head(list);
    while(node != NULL){
        AxisCoordinates *axis_coordinates = node_get_coordinates(node);
        if(axis_coordinates_get_y(axis_coordinates) == column){
            return node;
        }
        if(node_get_row_next(node) == NULL){
            break;
        }
        node = node_get_row_next(node);
    }
    return NULL;
}

void matrix_print_with_null(Matrix *m){
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

void matrix_print_with_zeros(Matrix *m){
    int i = 0, j = 0;
    for(i = 0; i < m->rows_size; i++){
        printf("[ ");
        for(j = 0; j < m->columns_size; j++){
            Node *node = matrix_get_node_by_coordinates(m, i, j);
            printf("%.2lf, ", node_get_value(node));
        }
        printf("]");
        printf("\n");
    }
}

void matrix_sparse_print(Matrix *m){
    int i = 0, j = 0;
    for(i = 0; i < m->rows_size; i++){
        for(j = 0; j < m->columns_size; j++){
            Node *node = matrix_get_node_by_coordinates(m, i, j);
            if(node != NULL){
                axis_coordinates_print(node_get_coordinates(node));
                printf(": %.2lf\n", node_get_value(node));
            }
        }
    }
}

void matrix_sequential_fill(Matrix *m){
    int rows_size = m->rows_size;
    int columns_size = m->columns_size;
    int r_idx, c_idx;
    data_type count = 1;
    for(r_idx = 0; r_idx < rows_size; r_idx++){
        for(c_idx = 0; c_idx < columns_size; c_idx++){
            if(count == 0){
                count++;
                continue;
            }
            list_push_back(m->rows[r_idx], count, construct_axis_coordinates(r_idx, c_idx));
            count++;
        }
    }
}

void matrix_fill_zeros(Matrix *m){
    int v = 0;
    for(int i = 0; i < m->rows_size; i++){
        for(int j = 0; j < m->columns_size; j++){
            list_push_back(m->rows[i], v, construct_axis_coordinates(i, j));
        }
    }
}

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

Matrix *matrix_sum(Matrix* m1, Matrix* m2){
    Matrix *m = matrix_construct(m1->rows_size, m1->columns_size);
    matrix_set_row_size(m, m1->rows_size);
    matrix_set_column_size(m, m1->columns_size);
    matrix_rows_init(m, m1->rows_size);
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

void matrix_swap_columns(Matrix *m, int column1, int column2){
    int i = 0;
    Node* n1 = NULL;
    Node* n2 = NULL;
    while(i < m->rows_size){
        n1 = matrix_get_node_by_coordinates(m, i, column1);
        n2 = matrix_get_node_by_coordinates(m, i, column2);
        node_swap_columns(n1, n2);
        i+=1;
    }
    matrix_fix_nodes(m);
}

void matrix_insert_element(Matrix *m, int row, int column, data_type value){
    Node *n = matrix_get_node_by_coordinates(m, row, column);
    if(n != NULL){
        node_set_value(n, value);
        return;
    }
    Node* row_next = matrix_get_row_next_valid_node(m, row, column);
    Node* row_prev = matrix_get_row_previous_valid_node(m, row, column);
    Node* column_next = matrix_get_column_next_valid_node(m, row, column);
    Node* column_prev = matrix_get_column_previous_valid_node(m, row, column);
    n = node_construct(value, row_next, row_prev, column_next, column_prev, construct_axis_coordinates(row, column));
    list_insert(m->rows[row], n, column);
}

Matrix *matrix_slice(Matrix* m, AxisCoordinates* init, AxisCoordinates* end){
    int row_init = axis_coordinates_get_x(init);
    int row_end = axis_coordinates_get_x(end);
    int column_init = axis_coordinates_get_y(init);
    int column_end = axis_coordinates_get_y(end);

    Matrix *slice = matrix_construct();
    matrix_set_row_size(slice, abs(row_end - row_init + 1));
    matrix_set_column_size(slice, abs(column_end - column_init + 1));
    matrix_rows_init(slice, abs(row_end - row_init + 1));

    data_type values[slice->rows_size*slice->columns_size];

    Node* n = NULL;
    int count = 0;
    for(int i = row_init; i <= row_end; i++){
        for(int j = column_init; j <= column_end; j++){
            n = matrix_get_node_by_coordinates(m, i, j);
            if(n == NULL){
                values[count] = 0;
                count++;
                continue;
            }
            values[count] = node_get_value(n);
            count++;
        }
    }
    matrix_fill(slice, values);
    matrix_fix_nodes(slice);
    return slice;
}

Matrix *matrix_transpose(Matrix* m){
    Matrix *m_T = matrix_construct();
    matrix_set_row_size(m_T, m->columns_size);
    matrix_set_column_size(m_T, m->rows_size);
    matrix_rows_init(m_T, m->columns_size);

    data_type values[m->rows_size*m->columns_size];
    Node* n = NULL;
    int count = 0;
    for(int i = 0; i < m->columns_size; i++){
        for(int j = 0; j < m->rows_size; j++){
            n = matrix_get_node_by_coordinates(m, j, i);
            if(n == NULL){
                values[count] = 0;
                count++;
                continue;
            }
            values[count] = node_get_value(n);
            count++;
        }
    }
    matrix_fill(m_T, values);
    matrix_fix_nodes(m_T);
    return m_T;
}

data_type matrix_sum_all(Matrix* m){
    int matrix_rows_size = m->rows_size;
    int matrix_columns_size = m->columns_size;
    int matrix_row_idx, matrix_column_idx;
    data_type sum = 0;
    for(matrix_row_idx = 0; matrix_row_idx < matrix_rows_size; matrix_row_idx++){
        for(matrix_column_idx = 0; matrix_column_idx < matrix_columns_size; matrix_column_idx++){
            Node * n = matrix_get_node_by_coordinates(m, matrix_row_idx, matrix_column_idx);
            if(n == NULL){
                continue;
            }
            sum+= node_get_value(n);
        }
    }
    return sum;
}

Matrix *matrix_convolution(Matrix* m, Matrix* kernel){
    int matrix_rows_size = m->rows_size;
    int matrix_columns_size = m->columns_size;
    int matrix_row_idx, matrix_column_idx;

    int kernel_rows_size = kernel->rows_size;
    int kernel_columns_size = kernel->columns_size;

    int r_init = -(kernel_rows_size-1)/2;
    int c_init = -(kernel_columns_size-1)/2;
    int r_end = -r_init;
    int c_end = -c_init;
    int c_init_save = c_init;
    int c_end_save = c_end;
    
    AxisCoordinates *init = construct_axis_coordinates(r_init, c_init);
    AxisCoordinates *end = construct_axis_coordinates(r_end, c_end);
    
    Matrix *convolution_result = matrix_construct();
    matrix_set_row_size(convolution_result, matrix_rows_size);
    matrix_set_column_size(convolution_result, matrix_columns_size);
    matrix_rows_init(convolution_result, matrix_rows_size);

    Matrix* kernel_x_matrix = NULL;
    Matrix *m_slice = NULL;
    
    data_type values[matrix_rows_size*matrix_columns_size];
    int pos = 0;

    for(matrix_row_idx = 0; matrix_row_idx < matrix_rows_size; matrix_row_idx++){
        c_init = c_init_save;
        c_end = c_end_save;
        axis_coordinates_update_y(init, c_init);
        axis_coordinates_update_y(end, c_end);

        for(matrix_column_idx = 0; matrix_column_idx < matrix_columns_size; matrix_column_idx++){
            m_slice = matrix_slice(m, init, end);
            matrix_fix_nodes(m_slice);

            kernel_x_matrix = matrix_multiplication_by_coordinates(m_slice, kernel);
            values[pos] = matrix_sum_all(kernel_x_matrix);

            c_end++;
            c_init++;
            axis_coordinates_update_y(init, c_init);
            axis_coordinates_update_y(end, c_end);
            pos++;
            matrix_destroy(m_slice);
            matrix_destroy(kernel_x_matrix);
        }
        r_end++;
        r_init++;
        axis_coordinates_update_x(init, r_init);
        axis_coordinates_update_x(end, r_end);
    }
    matrix_fill(convolution_result, values);
    matrix_fix_nodes(convolution_result);

    axis_coordinates_destroy(init);
    axis_coordinates_destroy(end);
    return convolution_result;
}

void matrix_destroy(Matrix *m){
    for(int i = 0; i < m->rows_size; i++){
        list_destroy(m->rows[i]);
    }
    free(m->rows);
    free(m);
}