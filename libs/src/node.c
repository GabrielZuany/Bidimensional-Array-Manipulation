#include "../include/node.h"
#include <stdlib.h>

struct Node
{
    data_type value;
    struct Node *next;
    struct Node *prev;
    AxisCoordinates *coordinates;
};

Node* node_construct(data_type value, Node *next, Node *prev, AxisCoordinates *coordinates){
    Node *node = (Node *)malloc(sizeof(Node));
    node->value = value;
    node->next = next;
    node->prev = prev;
    node->coordinates = coordinates;
    return node;
}

Node* node_get_next(Node *n){
    return n->next;
}

Node* node_get_previous(Node *n){
    return n->prev;
}

data_type node_get_value(Node *n){
    return n->value;
}

Node* node_get_coordinates(Node *n){
    return n->coordinates;
}

void node_set_next(Node *n, Node *next){
    n->next = next;
}

void node_set_previous(Node *n, Node *prev){
    n->prev = prev;
}

void node_set_value(Node *n, data_type value){
    n->value = value;
}

void node_set_coordinates(Node *n, AxisCoordinates *coordinates){
    n->coordinates = coordinates;
}

void node_print_coordinates(Node *n){
    printf("(%d, %d)\n", axis_coordenates_get_x(node_get_coordinates(n)), axis_coordenates_get_y(node_get_coordinates(n)));
}

void node_destroy(Node *n){
    free(n);
}

void node_destroy_Rec(Node* n){
    if (n==NULL){
        return;
    }
    node_destroy_Rec(n->next);
    node_destroy(n);
}