#include <stdlib.h>
#include <stdio.h>
#include "../include/list.h"
#include "../include/node.h"

struct List
{
    Node *head;
    Node *last;
    int size;
};

List *list_construct(){
    List *list = (List *)malloc(sizeof(List));
    list->head = NULL;
    list->last = NULL;
    list->size = 0;
    return list;
}

Node* list_get_head(List *l){
    return l->head;
}

void list_set_head(List *l, Node *head){
    l->head = head;
}

int list_size(List *l){
    return l->size;
}

void list_push_front(List *l, data_type data, AxisCoordinates *coordinates){
    Node * N = node_construct(data, l->head, NULL, NULL, NULL, coordinates);
    if(l->size == 0){
        l->head = N;
        l->last = N;
    }else{
        node_set_row_previous(l->head, N);
    }
    l->head = N;
    l->size++;
}

void list_push_back(List *l, data_type data, AxisCoordinates *coordinates){
    Node *row_next = NULL;
    Node *row_previous = l->last;
    Node *column_next = NULL;
    Node *column_previous = NULL;

    Node * N = node_construct(data, row_next, row_previous, column_next, column_previous, coordinates);
    if(l->size == 0){
        l->head = N;
        l->last = N;
    }
    else{
        node_set_row_next(l->last, N);
        l->last = node_get_row_next(l->last);
    }
    l->size++;
}

void list_print(List *l, void (*print_fn)(data_type)){
    Node* reference = l->head;
    printf("[");
    while(l->head != NULL){
        print_fn(node_get_value(l->head));
        if(node_get_row_next(l->head) != NULL){ 
            printf(", "); 
        }

        l->head = node_get_row_next(l->head);
    }
    printf("]\n");
    l->head = reference;
}

void list_print_reverse(List *l, void (*print_fn)(data_type)){
    Node* last_ref = l->last;

    printf("[");
    while(last_ref != NULL){
        print_fn(node_get_value(last_ref));
        if(node_get_row_previous(last_ref) != NULL) 
            printf(", "); 

        last_ref = node_get_row_previous(last_ref);
    }
    printf("]");
}

data_type list_get(List *l, int i){
    int count = 0;
    data_type val = 0;
    int len = list_size(l);
    Node* reference = l->head;

    while(count < len){
        if(count == i){
            val = node_get_value(l->head);
            l->head = reference;
            return val;
        }
        l->head = node_get_row_next(l->head);
        count++;
    }
    return -999;
}

data_type list_pop_front(List *l){
    Node* reference = node_get_row_next(l->head);
    data_type val = node_get_value(l->head);
    
    free(l->head);

    l->head = reference;
    if(l->head != NULL)
        node_set_row_previous(l->head, NULL);
    l->size--;

    return val;
}

data_type list_pop_back(List *l){
    Node* reference = node_get_row_previous(l->last);
    data_type val = node_get_value(l->last);
    
    free(l->last);

    l->last = reference;
    if(l->last != NULL)
        node_set_row_next(l->last, NULL);
    l->size--;

    return val;
}

List *list_reverse(List *l){
    List* reversed_list = list_construct();
    int size = list_size(l), count = 0;
    data_type value;
    while(count < size){
        value = list_get(l, count);
        list_push_front(reversed_list, value, NULL);
        count++;
    }
    return reversed_list;
}

void list_remove(List *l, data_type val){
    Node *n = l->head, *prev = NULL,*new_n = NULL;
    while (n != NULL) {
        if (node_get_value(n) == val) {
            if (prev == NULL){
                new_n = node_get_row_next(n);
                l->head = new_n;
            }
            else{
                new_n = node_get_row_next(n);
                node_set_row_next(prev, new_n);
            }
            node_destroy(n);
            n = new_n;
            l->size--;
        }
        else {
            prev = n;
            n = node_get_row_next(n);
        }
    }
}

void list_cat(List *l, List *m){
    Node* reference = l->head;
    while(l->head != NULL){
        l->head = node_get_row_next(l->head);
    }
    l->head = m->head;
    l->head = reference;
}

void list_destroy(List *l){
    node_destroy_Rec(l->head);
    free(l);
}
