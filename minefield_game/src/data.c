#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data.h"

#define SIZE_NAME 50

void add_player(Player **head, Player **tail, char *player_name, int player_score){
    Player *new_player = (Player*) malloc(sizeof(Player));
    strcpy(new_player->name, player_name);
    new_player->score = player_score;
    new_player->next = NULL;

    if(*head == NULL){
        *head = new_player;
        *tail = new_player;
    }
    else{
        (*tail)->next = new_player;
        *tail = new_player;
    }
}

void order_players(Player *head){
    Player *i, *j;

    for(i = head; i->next != NULL; i = i->next){
        for(j = i->next; j!= NULL; j = j->next){
            if(i->score > j->score || (i->score == j->score && strcmp(i->name, j->name) > 1)){
                swap(i, j);
            }
        }
    }
}

void swap(Player *a, Player *b){
    char aux_name[SIZE_NAME];
    float aux_score;

    strcpy(aux_name, a->name);
    aux_score = a->score;

    strcpy(a->name, b->name);
    a->score = b->score;
    
    strcpy(b->name, aux_name);
    b->score = aux_score;
}

void free_list(Player *head){
    Player *aux;

    while(head != NULL){
        aux = head;
        head = head->next;
        free(aux);
    }
}