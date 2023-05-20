#ifndef _MATRIX_H
#define _MATRIX_H

#include "list.h"
#include "node.h"

typedef struct Matrix Matrix;


/**
 * @brief Construct a new Matrix struct
 * 
 * @return Matrix* 
 * 
 * @note The matrix is initialized with 0 rows and 0 columns
 * @note Complexity: O(1). Is not necessary to iterate over the matrix.
 */
Matrix *matrix_construct();


/**
 * @brief Save the matrix in a binary file
 * 
 * @param m matrix to save
 * @param filename output file
 * 
 * @note Complexity: O(N)*O(M). 
 * N is the complexity to iterate over the matrix (N is a param to resume columns and rows in one variable).
 * M is the complexity to another needed function (matrix_get_node_by_coordinates) that is O(N) too.
 */
void matrix_save_binary(Matrix *m, char *filename);


/**
 * @brief Read a matrix from a binary file
 * 
 * @param filename input file
 * @return Matrix* 
 * 
 * @note Complexity: O(N)*O(M)*O(K)*O(L).
 * O(N) is the complexity to iterate over the matrix (N is a param to resume columns and rows in one variable).
 * O(M) is the complexity to another needed function (matrix_get_node_by_coordinates) that is O(N) too.
 * O(K) is the complexity to another needed function (matrix_fill) that is O(N) too.
 * O(L) is the complexity to another needed function (matrix_fix_nodes) that is O(C^2)*O(R^2).
 * 
 * (Where C is the cost of iterate over the columns and R is the cost of iterate over the rows)..
 */
Matrix *matrix_read_binary(char *filename);


/**
 * @brief Initialize the matrix with a number of rows
 * 
 * @param m 
 * @param size
 * 
 * @note Complexity: O(1). Is not necessary to iterate over the matrix. 
 */
void matrix_rows_init(Matrix *m, int size);


/**
 * @brief Set the matrix number of rows
 * 
 * @param m 
 * @param size
 * 
 * @note Complexity: O(1). Is not necessary to iterate over the matrix. 
 */
void matrix_set_row_size(Matrix *m, int size);


/**
 * @brief Set the matrix number of columns
 * 
 * @param m 
 * @param size
 * 
 * @note Complexity: O(1). Is not necessary to iterate over the matrix. 
 */
void matrix_set_column_size(Matrix *m, int size);


/**
 * @brief Get the matrix number of rows
 * 
 * @param m 
 * @return int
 * 
 * @note Complexity: O(1). Is not necessary to iterate over the matrix.  
 */
int matrix_get_row_size(Matrix *m);


/**
 * @brief Get the matrix number of columns
 * 
 * @param m 
 * @return int
 * 
 * @note Complexity: O(1). Is not necessary to iterate over the matrix.  
 */
int matrix_get_column_size(Matrix *m);


/**
 * @brief Get the node by coordinates.
 * 
 * @param m 
 * @param row 
 * @param column 
 * @return Node* 
 * 
 * @note Complexity: O(N). N is the number of rows or columns. (N is a param to resume columns and rows in one variable)
 * Best case: O(1). The node is in the first coordinate.
 * Worst case: O(N). The node is in the last coordinate.
 * Middle case: O(N/2). The node is in the center of the matrix.
 */
Node *matrix_get_node_by_coordinates(Matrix *m, int row, int column);


/**
 * @brief fill the matrix with sequential values (starting in 1 and ending in length of matrix)
 * 
 * @param m 
 * 
 * @note Complexity: O(N). Is necessary to iterate over the matrix. 
 * (N is a param to resume columns and rows in one variable).
 */
void matrix_sequential_fill(Matrix *m);


/**
 * @brief fill the matrix with array of values.
 * 
 * @param m 
 * 
 * @note Complexity: O(N). Is necessary to iterate over the matrix. 
 * (N is a param to resume columns and rows in one variable).
 */
void matrix_fill(Matrix *m, data_type *values);


/**
 * @brief fill the matrix with zeros. 
 * 
 * @param m 
 * 
 * @note Complexity: O(N). Is necessary to iterate over the matrix. 
 * (N is a param to resume columns and rows in one variable).
 * 
 * @note Initialize the matrix with any zero means that the matrix is sparse, so anyones nodes are created.
 */
void matrix_fill_zeros(Matrix *m);


/**
 * @brief fix each node internal pointers (up, down, left, right).
 * 
 * @param m 
 * 
 * @note Complexity: O(C^2)*(R^2). 
 * (Where C is the cost of iterate over the columns and R is the cost of iterate over the rows).
 */
void matrix_fix_nodes(Matrix *m);


/**
 * @brief print the matrix in stdout.
 * 
 * @param m 
 * 
 * @note Complexity: O(N). Is necessary to iterate over the matrix. 
 * (N is a param to resume columns and rows in one variable).
 */
void matrix_print_with_null(Matrix *m);


/**
 * @brief print the matrix in stdout.
 * 
 * @param m 
 * 
 * @note Complexity: O(N). Is necessary to iterate over the matrix. 
 * (N is a param to resume columns and rows in one variable).
 */
void matrix_print_with_zeros(Matrix *m);


/**
 * @brief print the matrix in stdout (only not null values and their coordinates).
 * 
 * @param m 
 * 
 * @note Complexity: O(N). Is necessary to iterate over the matrix. 
 * (N is a param to resume columns and rows in one variable).
 */
void matrix_sparse_print(Matrix *m);


/**
 * @brief create a new matrix with the sum between 2 given matrix.
 * 
 * @param m1 
 * @param m2 
 * @return Matrix* 
 * 
 * @note Complexity: O(N) * O(M^2) * O(K) * O(L). Is necessary to iterate over the matrix.
 * O(N) is the complexity to iterate over the matrix coordinates (N is a param to resume columns and rows in one variable).
 * O(M^2) is the complexity to another needed function twice (matrix_get_node_by_coordinates) that is O(N) too.
 * O(K) is the complexity to another needed function (matrix_fill) that is O(N) too.
 * O(L) is the complexity to another needed function (matrix_fix_nodes) that is O(C^2)*O(R^2).
 */
Matrix *matrix_sum(Matrix* m1, Matrix* m2);


/**
 * @brief create a new matrix with the multiplication between 2 given matrix (coordinates by coordinates).
 * 
 * @param m1 
 * @param m2 
 * @return Matrix* 
 * 
 * @note Complexity: O(N) * O(M^2) * O(K) * O(L). Is necessary to iterate over the matrix.
 * O(N) is the complexity to iterate over the matrix coordinates (N is a param to resume columns and rows in one variable).
 * O(M^2) is the complexity to another needed function twice (matrix_get_node_by_coordinates) that is O(N) too.
 * O(K) is the complexity to another needed function (matrix_fill) that is O(N) too.
 * O(L) is the complexity to another needed function (matrix_fix_nodes) that is O(C^2)*O(R^2).
 */
Matrix *matrix_multiplication_by_coordinates(Matrix* m1, Matrix* m2);


//utilizar a de insercao no lugar pra economizar processamento.
Matrix *matrix_multiplication_by_value(Matrix* m1, data_type value);

Matrix *matrix_multiplication(Matrix *m1, Matrix *m2);

void matrix_swap_rows(Matrix *m, int row1, int row2);

void matrix_swap_columns(Matrix *m, int column1, int column2);

void matrix_insert_element(Matrix *m, int row, int column, data_type value);

Matrix *matrix_slice(Matrix* m, AxisCoordinates* init, AxisCoordinates* end);

Matrix *matrix_transpose(Matrix* m);

Matrix *matrix_convolution(Matrix* m, Matrix* kernel);

void matrix_destroy(Matrix *m);

#endif 