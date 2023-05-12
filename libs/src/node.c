#include "../include/node.h"
#include "../include/axis_coordinates.h"
#include <stdlib.h>
#include <stdio.h>

struct Node
{
    data_type value;
    struct Node *row_next;
    struct Node *row_prev;
    struct Node *column_next;
    struct Node *column_prev;
    AxisCoordinates *coordinates;
};

Node* node_construct(data_type value, Node *row_next, Node *row_prev, Node *column_next, Node *column_prev, AxisCoordinates *coordinates){
    Node *node = (Node *)malloc(sizeof(Node));
    node->value = value;
    node->row_next = row_next;
    node->row_prev = row_prev;
    node->column_next = column_next;
    node->column_prev = column_prev;
    node->coordinates = coordinates;
    return node;
}

Node* node_get_row_next(Node *n){
    return n->row_next;
}

Node* node_get_row_previous(Node *n){
    return n->row_prev;
}

Node* node_get_column_next(Node *n){
    return n->column_next;
}

Node* node_get_column_previous(Node *n){
    return n->column_prev;
}

data_type node_get_value(Node *n){
    return n->value;
}

AxisCoordinates* node_get_coordinates(Node *n){
    return n->coordinates;
}

void node_set_row_next(Node *n, Node *next){
    n->row_next = next;
}

void node_set_row_previous(Node *n, Node *prev){
    n->row_prev = prev;
}

void node_set_column_next(Node *n, Node *next){
    n->column_next = next;
}

void node_set_column_previous(Node *n, Node *prev){
    n->column_prev = prev;
}

void node_set_value(Node *n, data_type value){
    n->value = value;
}

void node_set_coordinates(Node *n, AxisCoordinates *coordinates){
    n->coordinates = coordinates;
}

void node_print_coordinates(Node *n){
    AxisCoordinates *coordinates = node_get_coordinates(n);
    printf("(%d, %d)", axis_coordenates_get_x(coordinates), axis_coordenates_get_y(coordinates));
}

void node_destroy(Node *n){
    free(n);
}

void node_destroy_Rec(Node* n){
    if (n==NULL){
        return;
    }
    axis_coordenates_destroy(node_get_coordinates(n));
    node_destroy_Rec(n->row_next);
    node_destroy(n);
}