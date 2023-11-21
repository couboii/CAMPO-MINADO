#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/select.h>
#include <unistd.h>

#include "screen.h"
#include "keyboard.h"
#include "timer.h"
#include "data.h"
#include "animations.h"

#define SIZE_NAME 50

// variaveis globais 
Celula game [10][10];
int l, c, size = 10;
Player *head = NULL, *tail = NULL;

// inicializar jogo zerado
void inicializarjogo(){
   for(l = 0; l <size; l++){
    for(c = 0; c < size; c++){
        game[l][c].is_bomb = 0;
        game[l][c].closed_or_open = 0;
        game[l][c].near_bombs = 0;
    }
   }
}
// verificar se a posicao par de coordenadas é válido
int coordenadaEhValida(int l, int c){
    if(l >= 0 && l < size && c >= 0 && c < size)
      return 1;
    else
      return 0;
}
// funcao que retorna a quantidade de bombas na vizinhaca de l c
int quantBombasVizinhas(int l, int c){
    int quantidade = 0;
    // Esquerda
    if (coordenadaEhValida(l - 1, c) && game[l - 1][c].is_bomb) quantidade++;
    // Cima-Esquerda
    if (coordenadaEhValida(l - 1, c - 1) && game[l - 1][c - 1].is_bomb) quantidade++;
    // Cima
    if (coordenadaEhValida(l, c - 1) && game[l][c - 1].is_bomb) quantidade++;
    // Cima-Direita
    if (coordenadaEhValida(l + 1, c - 1) && game[l + 1][c - 1].is_bomb) quantidade++;
    // Direitra
    if (coordenadaEhValida(l + 1, c) && game[l + 1][c].is_bomb) quantidade++;
    // Baixo-Direita
    if (coordenadaEhValida(l + 1, c + 1) && game[l + 1][c + 1].is_bomb) quantidade++;
    // Baixo
    if (coordenadaEhValida(l, c + 1) && game[l][c + 1].is_bomb) quantidade++;
    // Baixo-Esquerda
    if (coordenadaEhValida(l - 1, c + 1) && game[l - 1][c + 1].is_bomb) quantidade++;
    
    return quantidade;
}
// procedimento para sortear N bombas
void sortearBombas(int n){
    int i;
    srand(time(NULL));
    for(i = 1; i <= n; i++){
        l = rand() % size;
        c = rand() % size;
        if(game[l][c].is_bomb == 0)
        game[l][c].is_bomb = 1;
        else
            i--;      
    }
}
// contar as bombas  vizinhas
void contarBombas(){
    for(l = 0; l <size; l++){
    for(c = 0; c < size; c++){
        game[l][c].near_bombs = quantBombasVizinhas(l , c);
    }
    }
}
// procedimento para imprimir o jogo
void imprimir(){
    system("clear");
    // printf("\n\n\t\t\t CAMPO MINADO \n");
    screenSetColor(WHITE, DARKGRAY);
    printf("\n \n \t  ");

    for(l = 0; l < size; l++){
      screenSetColor(GREEN, DARKGRAY);
      printf("   %d", l);
    }
    screenSetColor(WHITE, DARKGRAY);

    printf("\n\t   -----------------------------------------\n");
    // printf("\n\t   ─────────────────────────────────────────\n");
    // printf("\n\t   ⎶⎶⎶⎶⎶⎶⎶⎶⎶⎶⎶⎶⎶⎶⎶⎶⎶⎶⎶⎶⎶⎶⎶⎶⎶⎶⎶⎶⎶⎶⎶⎶⎶⎶⎶⎶⎶⎶⎶⎶⎶\n");

    for(l = 0; l <size; l++){
      screenSetColor(GREEN, DARKGRAY);
      printf("\t%d  ", l);
      screenSetColor(WHITE, DARKGRAY);
      printf("|");

     for(c = 0; c < size; c++){
        if(game[l][c].closed_or_open){
            if(game[l][c].is_bomb){
              screenSetColor(BLACK, DARKGRAY);
              printf("💣 ");
              screenSetColor(WHITE, DARKGRAY);
            }
            else{
              int nearBombs = game[l][c].near_bombs;

              switch (nearBombs) {
              case 0:
                screenSetColor(WHITE, DARKGRAY);
                break;
              case 1:
                screenSetColor(BLUE, DARKGRAY);
                break;
              case 2:
                screenSetColor(LIGHTGREEN, DARKGRAY);
                break;
              case 3:
                screenSetColor(RED, DARKGRAY);
                break;
              case 4:
                screenSetColor(LIGHTMAGENTA, DARKGRAY);
                break;
              default:
                screenSetColor(MAGENTA, DARKGRAY);
                break;
              }
              printf(" %d ", game[l][c].near_bombs);
              screenSetColor(WHITE, DARKGRAY);
            }
             

        }
        else
          printf("   ");
        printf("|");
    }
    printf("\n\t   -----------------------------------------\n");
    // printf("\n\t   ─────────────────────────────────────────\n");
    }
    printf("\n");
}
// procedimento para abrir coordenada digitada pelo usuario
void abrirCelula(int l, int c){
  if(coordenadaEhValida(l, c) == 1 && game[l][c].closed_or_open == 0){
    game[l][c].closed_or_open = 1;
    if(game[l][c].near_bombs == 0){
        abrirCelula(l -1 , c);
        abrirCelula(l -1 , c -1);
        abrirCelula(l -1 , c +1);
        abrirCelula(l +1 , c);
        abrirCelula(l +1 , c -1);
        abrirCelula(l +1 , c +1);
        abrirCelula(l, c + 1);
        abrirCelula(l, c - 1);
    }
  }
}
// funcao para verificar vitoria 1- ganhou 0 - nao ganhou ainda
int ganhou(){
    int quantidade = 0;
    for(l = 0; l <size; l++){
    for(c = 0; c < size; c++){
        if(game[l][c].closed_or_open == 0 && game[l][c].is_bomb == 0)
          quantidade++;
    }
   }
   return quantidade;
}

void jogar() {
    int linha, coluna;
    char player_name[SIZE_NAME];

    if(head != NULL)getchar();
    printf("\n\n\nINSIRA SEU USERNAME: ");
    fgets(player_name, sizeof(player_name), stdin);
 
    timerInit(0);

    do {
        imprimir();

        int inputDisponivel = 0;
        while (!inputDisponivel) {
            fd_set set;
            struct timeval timeout;

            // Inicializa o conjunto de file descriptors e o timeout
            FD_ZERO(&set);
            FD_SET(STDIN_FILENO, &set);
            timeout.tv_sec = 1;  // Timeout de 1 segundo
            timeout.tv_usec = 0;

            // Move o cursor uma linha para cima, limpa a linha, exibe o tempo
            // printf("\033[A\33[2K"); // Move para cima e limpa a linha
            
            // int timeDiff = getTimeDiff();

            // printf("\033[A\r"); // Volta pra linha de cima
            printf("\r");
            // printf("%d Digite as coordenadas da linha e coluna: \n", timeDiff); // Salva a posicao do cursor
            printf("Digite as coordenadas da linha e coluna: \x1b[s\n"); // Salva a posicao do cursor
            // printf("Digite as coordenadas da linha: \x1b[s\n"); // Salva a posicao do cursor
            // printf("Digite as coordenadas da coluna: \x1b[s\n"); // Salva a posicao do cursor
            screenHideCursor();
            screenSetColor(RED, DARKGRAY);
            printf("🕐 Tempo: ");
            timerPrint();
            printf("s");
            screenSetColor(WHITE, DARKGRAY);
            // screenShowCursor();
            printf("\x1b[u");
            // printf("\33[100C[u");
            
            // printf("\x1b[u");   // volta para a posicao salva

            fflush(stdout);  // Garante que o texto seja exibido imediatamente

            // Verifica se há entrada disponível
            if (select(STDIN_FILENO + 1, &set, NULL, NULL, &timeout) > 0) {
                // scanf("%d %d", &linha, &coluna);
                scanf("%d", &linha);
                scanf("%d", &coluna);
                if (coordenadaEhValida(linha, coluna) == 0 || game[linha][coluna].closed_or_open == 1) {
                    imprimir();
                    screenSetColor(RED, DARKGRAY);
                    printf("\nCoordenada inválida ou já aberta ;( insira um valor válido\n\n");
                    screenSetColor(WHITE, DARKGRAY);
                } else {
                    inputDisponivel = 1;
                }
            }
        }

        abrirCelula(linha, coluna);
    } while (ganhou() != 0 && game[linha][coluna].is_bomb == 0);

    imprimir();
    usleep(2500000);
    system("clear");

    int win_or_lost;

    if (game[linha][coluna].is_bomb == 1){
      win_or_lost = 0;
      game_over();
    }
    else{
      win_or_lost = 1;
      you_win();
    }

    int time = (getTimeDiff()/1000) * win_or_lost;
    screenSetColor(RED, DARKGRAY);
    printf("\nSCORE: %d", time);
    screenSetColor(WHITE, DARKGRAY);

    add_player(&head, &tail, player_name, time);
    timerDestroy();
    screenShowCursor();
}

int main(){
    int opcao;
    project_presentation();

    do{
      inicializarjogo();
      sortearBombas(size);
      contarBombas();
      campo_minado_presentation();

      jogar();

      printf("\n\nDIGITE 1 PARA JOGAR NOVAMENTE: ");
      scanf("%d", &opcao);
    }while(opcao == 1);

    if(head != NULL){
      order_players(head);
      print_podium(head);
      free_list(head);
    }

    screenShowCursor();
    return 0;
}