#ifndef _NODE_H_
#define _NODE_H_

#include "../include/axis_coordinates.h"

typedef int data_type;
typedef struct Node Node;

Node *node_construct(data_type value, Node *next, Node *prev, AxisCoordinates *coordinates);

Node* node_get_next(Node *n);

Node* node_get_previous(Node *n);

data_type node_get_value(Node *n);

Node* node_get_coordinates(Node *n);

void node_set_next(Node *n, Node *next);

void node_set_previous(Node *n, Node *prev);

void node_set_value(Node *n, data_type value);

void node_set_coordinates(Node *n, AxisCoordinates *coordinates);

void node_print_coordinates(Node *n);

void node_destroy(Node *n);

void node_destroy_Rec(Node* n);

#endif