#include <stdio.h>
#include <stdlib.h>

#include "data.h"

typedef struct Node{
    int is_bomb; //0 = não e 1 = sim
    int closed_or_open; //0 = fechado e 1 = aberto
    int near_nodes; //quantidade de bombas próximas
    struct Node *next;
} Node;

void add_node(Node **head, Node **tail, int is_bomb, int closed_or_open, int near_nodes){
    Node *new_node = (Node*) malloc(sizeof(Node));
    new_node->is_bomb = is_bomb;
    new_node->closed_or_open = closed_or_open;
    new_node->near_nodes = near_nodes;
    new_node->next = NULL;

    if(*head == NULL){
        *head = new_node;
        *tail = new_node;
    }
    else{
        (*tail)->next = new_node;
        *tail = new_node;
    }
}