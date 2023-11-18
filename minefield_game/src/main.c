#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "screen.h"
#include "keyboard.h"
#include "timer.h"
#include "data.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct {
 int eBomba;
 int estaAberta;
 int vizinhos;
}Celula;

// variaveis globais 
Celula jogo [10][10];
int l, c, tam = 10; 

// inicializar jogo zerado
void inicializarjogo(){
   for(l = 0; l <tam; l++){
    for(c = 0; c < tam; c++){
        jogo[l][c].eBomba = 0;
        jogo[l][c].estaAberta = 0;
        jogo[l][c].vizinhos = 0;
    }
   }
}
// verificar se a posicao par de coordenadas é válido
int coordenadaEhValida(int l, int c){
    if(l >= 0 && l < tam && c >= 0 && c < tam)
      return 1;
    else
      return 0;
}
// funcao que retorna a quantidade de bombas na vizinhaca de l c
int quantBombasVizinhas(int l, int c){
    int quantidade = 0;
    if (coordenadaEhValida(l - 1, c) && jogo[l - 1][c].eBomba)
      quantidade++;
    if (coordenadaEhValida(l + 1, c) && jogo[l + 1][c].eBomba)
      quantidade++;
    if (coordenadaEhValida(l, c - 1) && jogo[l][c - 1].eBomba)
      quantidade++;
    if (coordenadaEhValida(l, c + 1) && jogo[l][c + 1].eBomba)
      quantidade++;
    return quantidade;
}
// procedimento para sortear N bombas
void sortearBombas(int n){
    int i;
    srand(time(NULL));
    for(i = 1; i <= n; i++){
        l = rand() % tam;
        c = rand() % tam;
        if(jogo[l][c].eBomba == 0)
        jogo[l][c].eBomba = 1;
        else
            i--;      
    }
}
// contar as bombas  vizinhas
void contarBombas(){
    for(l = 0; l <tam; l++){
    for(c = 0; c < tam; c++){
        jogo[l][c].vizinhos = quantBombasVizinhas(l , c);
    }
    }
}
// procedimento para imprimir o jogo
void imprimir(){
    printf("\n \n \t");
    for(l = 0; l < tam; l++)
      printf("   %d", l); // indices das colunas
    printf("\n\t   -----------------------------------------\n");
    for(l = 0; l <tam; l++){
        printf("\t%d  |", l); // incdices das linhas
     for(c = 0; c < tam; c++){
        if(jogo[l][c].estaAberta){
            if(jogo[l][c].eBomba)
               printf(" * ");
            else
               printf(" %d ", jogo[l][c].vizinhos);
        }
        else
          printf("   ");
        printf("|");
    }
    printf("\n\t   -----------------------------------------\n");
    }
}
// procedimento para abrir coordenada digitada pelo usuario
void abrirCelula(int l, int c){
  if(coordenadaEhValida(l, c) == 1 && jogo[l][c].estaAberta == 0){
    jogo[l][c].estaAberta = 1;
    if(jogo[l][c].vizinhos == 0){
        abrirCelula(l -1 , c);
        abrirCelula(l +1 , c);
        abrirCelula(l, c + 1);
        abrirCelula(l, c - 1);
    }
  }
}
// funcao para verificar vitoria 1- ganhou 0 - nao ganhou ainda
int ganhou(){
    int quantidade = 0;
    for(l = 0; l <tam; l++){
    for(c = 0; c < tam; c++){
        if(jogo[l][c].estaAberta == 0 && jogo[l][c].eBomba == 0)
          quantidade++;
    }
   }
   return quantidade;
}
// procedimento jogar que fez a leitura coordenada
void jogar (){
    int linha, coluna;
    do{
        imprimir();
        do{
            printf("digite as coordenadas da linha e coluna: ");
            scanf("%d %d", &linha, &coluna);
            if(coordenadaEhValida(linha, coluna) == 0 || jogo[linha][coluna].estaAberta == 1)
               printf("coordenada invalida ou ja aberta ;( insira um válido");
        } while(coordenadaEhValida(linha, coluna) == 0 || jogo[linha][coluna].estaAberta == 1);
        abrirCelula(linha, coluna);
    }while(ganhou() != 0 && jogo[linha][coluna].eBomba == 0);
    if(jogo[linha][coluna].eBomba == 1)
      printf("\n\tvoce perdeu\n");
    else
      printf("\t parabens voce ganhou");
    imprimir();
}
int main(){
    int opcao;
    do{
      inicializarjogo();
      sortearBombas(10);
      contarBombas();
      printf("\n\t\t\t CAMPO MINADO \n");
      jogar();

      printf("\n digite 1 para jogar novamente:");
      scanf("%d", &opcao);
    }while(opcao == 1);

    return 0;
}