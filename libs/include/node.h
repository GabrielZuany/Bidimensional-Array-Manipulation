#ifndef _NODE_H_
#define _NODE_H_
#define null 0.0000001

#include "../include/axis_coordinates.h"

typedef double data_type;
typedef struct Node Node;

Node* node_construct(data_type value, Node *row_next, Node *row_prev, Node *column_next, Node *column_prev, AxisCoordinates *coordinates);

Node* node_get_row_next(Node *n);

Node* node_get_row_previous(Node *n);

Node* node_get_column_next(Node *n);

Node* node_get_column_previous(Node *n);

data_type node_get_value(Node *n);

AxisCoordinates* node_get_coordinates(Node *n);

void node_set_row_next(Node *n, Node *next);

void node_set_row_previous(Node *n, Node *prev);

void node_set_column_next(Node *n, Node *next);

void node_set_column_previous(Node *n, Node *prev);

void node_set_value(Node *n, data_type value);

void node_set_coordinates(Node *n, AxisCoordinates *coordinates);

void node_print_coordinates(Node *n);

void node_destroy(Node *n);

void node_destroy_Rec(Node* n);

#endif