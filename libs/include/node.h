#ifndef _NODE_H_
#define _NODE_H_
#define null 0.0000001

#include "../include/axis_coordinates.h"

typedef double data_type;
typedef struct Node Node;


/**
 * @brief Construct a new Node struct
 * 
 * @param value node value
 * @param row_next node right next pointer
 * @param row_prev node left previous pointer
 * @param column_next node down next pointer
 * @param column_prev node up previous pointer
 * @param coordinates node coordinates
 * @return Node* 
 * 
 * @note Complexity: O(1). Its not necessary to iterate over the list to construct a new node.
 */
Node* node_construct(data_type value, Node *row_next, Node *row_prev, Node *column_next, Node *column_prev, AxisCoordinates *coordinates);


/**
 * @brief Get the node right next pointer
 * 
 * @param n node
 * @return Node*
 * 
 * @note Complexity: O(1). Its not necessary to iterate over the list to get the next node. 
 */
Node* node_get_row_next(Node *n);


/**
 * @brief Get the node left previous pointer
 * 
 * @param n node
 * @return Node*
 * 
 * @note Complexity: O(1). Its not necessary to iterate over the list to get the previous node.  
 */
Node* node_get_row_previous(Node *n);


/**
 * @brief Get the node down next pointer
 * 
 * @param n node
 * @return Node*
 * 
 * @note Complexity: O(1). Its not necessary to iterate over the list to get the next node. 
 */
Node* node_get_column_next(Node *n);


/**
 * @brief Get the node up previous pointer
 * 
 * @param n node
 * @return Node*
 * 
 * @note Complexity: O(1). Its not necessary to iterate over the list to get the previous node.  
 */
Node* node_get_column_previous(Node *n);


/**
 * @brief Get the node value
 * 
 * @param n node
 * @return data_type 
 * 
 * @note Complexity: O(1). Its not necessary to iterate over the list to get the node value.  
 */
data_type node_get_value(Node *n);


/**
 * @brief Get the node coordinates
 * 
 * @param n node
 * @return AxisCoordinates* 
 * 
 * @note Complexity: O(1). Its not necessary to iterate over the list to get the node coordinates.  
 */
AxisCoordinates* node_get_coordinates(Node *n);


/**
 * @brief Set the node right next pointer
 * 
 * @param n node
 * @param next node right next pointer
 * 
 * @note Complexity: O(1). Its not necessary to iterate over the list to set the next node. 
 */
void node_set_row_next(Node *n, Node *next);


/**
 * @brief Set the node left previous pointer
 * 
 * @param n node
 * @param prev node left previous pointer
 * 
 * @note Complexity: O(1). Its not necessary to iterate over the list to set the previous node.  
 */
void node_set_row_previous(Node *n, Node *prev);


/**
 * @brief Set the node down next pointer
 * 
 * @param n node
 * @param next node down next pointer
 * 
 * @note Complexity: O(1). Its not necessary to iterate over the list to set the next node. 
 */
void node_set_column_next(Node *n, Node *next);


/**
 * @brief Set the node up previous pointer
 * 
 * @param n node
 * @param prev node up previous pointer
 * 
 * @note Complexity: O(1). Its not necessary to iterate over the list to set the previous node.  
 */
void node_set_column_previous(Node *n, Node *prev);


/**
 * @brief Set the node value
 * 
 * @param n node
 * @param value node value
 * 
 * @note Complexity: O(1). Its not necessary to iterate over the list to set the node value.  
 */
void node_set_value(Node *n, data_type value);


/**
 * @brief Set the node coordinates
 * 
 * @param n node
 * @param coordinates node coordinates
 * 
 * @note Complexity: O(1). Its not necessary to iterate over the list to set the node coordinates.  
 */
void node_set_coordinates(Node *n, AxisCoordinates *coordinates);


/**
 * @brief Swap the node in column level
 * 
 * @param n1 node 1
 * @param n2 node 2
 * 
 * @note Complexity: O(1). Its not necessary to iterate over the list to swap the node rows.  
 */
void node_swap_columns(Node* n1, Node* n2);


/**
 * @brief print the node coordinates
 * 
 * @param n node
 * 
 * @note Complexity: O(1). Its not necessary to iterate over the list to print the node coordinates.
 */
void node_print_coordinates(Node *n);


/**
 * @brief destroy the node
 * 
 * @param n node
 * 
 * @note Complexity: O(1). Its not necessary to iterate over the list to print the node value.
 */
void node_destroy(Node *n);


/**
 * @brief destroy all nodes recursively
 * 
 * @param n node
 * 
 * @note Complexity: O(N). Its necessary to iterate over the list to destroy all nodes.
 * In best case, the list is empty, so the complexity is O(1).
 */
void node_destroy_Rec(Node* n);

#endif