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
    if(n == NULL){
        return NULL;
    }
    return n->row_next;
}

Node* node_get_row_previous(Node *n){
    if(n == NULL){
        return NULL;
    }
    return n->row_prev;
}

Node* node_get_column_next(Node *n){
    if(n == NULL){
        return NULL;
    }
    return n->column_next;
}

Node* node_get_column_previous(Node *n){
    if(n == NULL){
        return NULL;
    }
    return n->column_prev;
}

data_type node_get_value(Node *n){
    if(n == NULL){
        return null;
    }
    return n->value;
}

AxisCoordinates* node_get_coordinates(Node *n){
    if(n == NULL){
        return NULL;
    }
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
    if(n == NULL){
        return;
    }
    n->coordinates = coordinates;
}

void node_swap_columns(Node* n1, Node* n2){
    data_type n1_value = node_get_value(n1);
    data_type n2_value = node_get_value(n2);

    if(n1 == NULL && n2 == NULL){
        return;
    }
    if(n1 == NULL && n2 != NULL){
        n1 = n2; 
        AxisCoordinates *coordinates_n2 = node_get_coordinates(n2);
        int y = axis_coordenates_get_y(coordinates_n2);
        y--;
        axis_coordinates_update_y(coordinates_n2, y);
        node_set_coordinates(n1, coordinates_n2);
        return;
    }
    if(n1 != NULL && n2 == NULL){
        n2 = n1;
        AxisCoordinates *coordinates_n1 = node_get_coordinates(n1);
        int y = axis_coordenates_get_y(coordinates_n1);
        y++;
        axis_coordinates_update_y(coordinates_n1, y);
        node_set_coordinates(n2, coordinates_n1);
        return;
    }
    
    node_set_value(n1, n2_value);
    node_set_value(n2, n1_value);
}

void node_print_coordinates(Node *n){
    AxisCoordinates *coordinates = node_get_coordinates(n);
    printf("(%d, %d)", axis_coordenates_get_x(coordinates), axis_coordenates_get_y(coordinates));
}

void node_destroy(Node *n){
    if (n==NULL){
        return;
    }
    free(n);
}

void node_destroy_Rec(Node* n){
    if (n==NULL){
        return;
    }
    if(node_get_coordinates(n) != NULL){
        axis_coordenates_destroy(node_get_coordinates(n));
    }
    
    node_destroy_Rec(n->row_next);
    node_destroy(n);
}