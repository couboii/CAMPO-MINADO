#ifndef DATA_H
#define DATA_H

typedef struct Celula{
    int is_bomb; //0 = não e 1 = sim
    int closed_or_open; //0 = fechado e 1 = aberto
    int near_bombs; //quantidade de bombas próximas
} Celula;

typedef struct Player{
    char name[50];
    int score;
    struct Player *next;
} Player;

void add_player(Player **head, Player **tail, char *player_name, int player_score);

void order_players(Player *head);

void swap(Player *a, Player *b);

void free_list(Player *head);

#endif