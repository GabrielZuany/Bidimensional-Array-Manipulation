#ifndef _LIST_H_
#define _LIST_H_

#include "node.h"

typedef struct List List;


/**
 * @brief Construct a new Linked List:: Linked List object
 *  Allocates memory for a new linked list and returns a pointer to it.
 * @return List*
 * Pointer to the newly allocated linked list.
 * @note Complexity: O(1). Constructor function only allocates memory for the struct. Is not necessary to iterate over the struct.
 *
 */
List *list_construct();


/**
 * @brief Get the head of the linked list
 * 
 * @param l linked list
 * @return Node* first node of the linked list
 * 
 * @note Complexity: O(1). Get first node of the linked list. Is not necessary to iterate over the struct.
 */
Node* list_get_head(List *l);


/**
 * @brief Set the head of the linked list
 * 
 * @param l linked list
 * @param head new head of the linked list
 * 
 * @note Complexity: O(1). Set first node of the linked list. Is not necessary to iterate over the struct.
 */
void list_set_head(List *l, Node *head);


/**
 * @brief Get the last(tail) of the linked list
 * 
 * @param l linked list
 * @param last tail of the linked list
 * 
 * @note Complexity: O(1). Get last node of the linked list. 
 * Is not necessary to iterate over the struct because the struct contains the tail pointer.
 * If the struct didn't contain the tail pointer, it would be necessary to iterate over the struct and complexity would be O(N).
 */
void list_set_last(List *l, Node *last);


/**
 * @brief Insert a new node in the linked list in the specified index.
 * 
 * @param l linked list
 * @param n new node
 * @param index index (position) where the new node will be inserted
 * 
 * @note Complexity: O(N). Insert a new node in the linked list in the specified index.
 * Is necessary to iterate over the struct to find the node in the specified index.
 * In best case it will be O(1) if the index is 0 (insert at the beginning of the linked list).
 * In worst case it will be O(N) if the index is N (insert at the end of the linked list).
 * The middle case is O(N/2) if the index is N/2 (insert in the middle of the linked list).
 */
void list_insert(List*l, Node* n, int index);


/**
 * @brief Returns the size of the linked list.
 *  Returns the number of nodes in the linked list.
 * @param l
 * Pointer to the linked list.
 * @return int
 * Number of nodes in the linked list.
 *
 * @note Complexity: O(1). The struct contains the list size. 
 * Cost more memory but we get a better performance if the size is needed multiple times.
 */
int list_size(List *l);


/**
 * @brief Pushes a new node to the front of the linked list.
 *  Allocates memory for a new node and inserts it at the front of the linked list.
 * @param l
 * Pointer to the linked list.
 * @param data
 * Pointer to the data to be stored in the new node.
 * @param coordinates
 * Pointer to the coordinates to be stored in the new node.
 *
 * @note Complexity: O(1). Insert a new node at the beginning of the linked list.
 */
void list_push_front(List *l, data_type data, AxisCoordinates *coordinates);


/**
 * @brief Pushes a new node to the back of the linked list.
 * Allocates memory for a new node and inserts it at the back of the linked list.
 * @param l
 * Pointer to the linked list.
 * @param data
 * Pointer to the data to be stored in the new node.
 * @param coordinates
 * Pointer to the coordinates to be stored in the new node.
 * 
 * @note Complexity: O(1). Insert a new node at the end of the linked list.
*/
void list_push_back(List *l, data_type data, AxisCoordinates *coordinates);


/**
 * @brief Pop the last node of the linked list and returns its data.
 * 
 * @param l linked list
 * @return data_type data stored in the last node of the linked list
 * 
 * @note Complexity O(1). Remove the last node of the linked list and fix the new last.
 */
data_type list_pop_back(List *l);


/**
 * @brief Print the elements of the linked list.
 *  Print the elements of the linked list.
 * @param l
 * Pointer to the linked list.
 * @param print_fn
 * Pointer to the function to print data_type values.
 *
 * @note Complexity: O(N). Iterate over the linked list to print all the elements.
 */
void list_print(List *l, void (*print_fn)(data_type));


/**
 * @brief Print the elements of the linked list in reverse order.
 * Print the elements of the linked list in reverse order.
 * @param l
 * Pointer to the linked list.
 * @param print_fn
 * Pointer to the function to print data_type values.
 * 
 * @note Complexity: O(N). Iterate over the linked list to print all the elements.
*/
void list_print_reverse(List *l, void (*print_fn)(data_type));


/**
 * @brief Returns the data stored in the node at the given index.
 * @param l
 * Pointer to the linked list.
 * @param i
 * Index of the node.
 * @return data_type
 * Data stored in the node at the given index.
 *
 * @note Complexity: O(N). Iterate over the linked list to find the node at the given index.
 * In best case it will be O(1) if the index is 0 (get the first node of the linked list).
 * In worst case it will be O(N) if the index is N (get the last node of the linked list).
 * The middle case is O(N/2) if the index is N/2 (get the node in the middle of the linked list).
 */
data_type list_get(List *l, int i);


/**
 * @brief Remove the first node of the linked list and returns its data.
 * @param l
 * Pointer to the linked list.
 * @return data_type
 * Pointer to the data stored in the first node of the linked list that was removed.
 *
 * @note Complexity: O(1). Remove the first node of the linked list and fix the new head.
 */
data_type list_pop_front(List *l);


/**
 * @brief Create a new list given by the reverse of the given list.
 * @param l
 * Pointer to the linked list.
 * @return List*
 * Pointer to the newly allocated linked list.
 * 
 * @note Complexity: O(N). Iterate over the linked list to create the new list.
 */
List *list_reverse(List *l);


/**
 * @brief Removes all nodes with the given value from the linked list.
 * Removes all nodes with the given value from the linked list and frees the memory allocated for them.
 * @param l
 * Pointer to the linked list.
 * @param val
 * Value to be removed from the linked list.
 * 
 * @note Complexity: O(N). Iterate over the linked list to find the nodes with the given value.
 * In best case it will be O(1) if the value is in the first node of the linked list.
 * In worst case it will be O(N) if the value is in all the nodes of the linked list.
 * The middle case is O(N/2) if the value is in N/2 nodes of the linked list.
 */
void list_remove(List *l, data_type val);


/**
 * @brief Destroys the linked list.
 *  Frees the memory allocated for the linked list and all its nodes.
 * @param l
 * Pointer to the linked list.
 *
 * @note Complexity: O(N). Iterate over the linked list to free the memory allocated for all its nodes.
 * In best case it will be O(1) if the linked list is empty.
 */
void list_destroy(List *l);

#endif