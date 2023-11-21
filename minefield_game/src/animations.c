#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 

#include "animations.h"
#include "screen.h"
#include "data.h"

#define SIZE_NAME 50

void game_over(){
    usleep(1000000);
    screenHideCursor();
	fflush(stdin);
    screenSetColor(RED, DARKGRAY);
	printf("\n\n");
	puts("");
	puts("                                              |-----------------------------------------------------------------------------|");
	puts("                                              | .--.   .--.             ^       ,----.              .-.                     |");
	puts("                                              | :  :   :  :            ^ ^     :      :             : :                     |");
	puts("                                              | :  :._.:  : .--. .---..---.    :  ,__:.---.,----, .-' :.---.  _   _         |");
	puts("                                              |  :        :' .; :: ::': :-'    :  :   : :-': ;-; ' .; :: :-''' .;  '        |");
	puts("                                              |   :..__..: `.__.'`.__,`.__;    :__:   `.__;:_:   `.__.'`.__; `.___.'        |");
	puts("                                              |                                                                             |");
	puts("                                              |                                                                             |");
	puts("                                              |-----------------------------------------------------------------------------|");
	
    screenSetColor(LIGHTGRAY, DARKGRAY);
	printf("                                                                               _______________         \n");
	printf("                                                                              /               \\       \n"); 
	printf("                                                                             /                 \\      \n");
	printf("                                                                           //                   \\/\\  \n");
	printf("                                                                           \\|   XXXX     XXXX   | /   \n");
	printf("                                                                            |   XXXX     XXXX   |/     \n");
	printf("                                                                            |   XXX       XXX   |      \n");
	printf("                                                                            |                   |      \n");
	printf("                                                                            \\__      XXX      __/     \n");
	printf("                                                                              |\\     XXX     /|       \n");
	printf("                                                                              | |           | |        \n");
	printf("                                                                              | I I I I I I I |        \n");
	printf("                                                                              |  I I I I I I  |        \n");
	printf("                                                                              \\_             _/       \n");
	printf("                                                                                \\_         _/         \n");
	printf("                                                                                  \\_______/           \n");
	fflush(stdin);
    usleep(2500000);
    screenShowCursor();
} 

void campo_minado_presentation(){
    system("clear");
    screenHideCursor();
    screenSetColor(GREEN, DARKGRAY);
	fflush(stdin);
	printf("\n\n");
	puts("                                              ---------------------------------------------------------------------------------");
	puts("                                              |     .--.                               .-..-. _                 .-.           |");
	puts("                                              |    : .--'                              : `' ::_;                : :           |");
	puts("                                              |    : :    .--.  ,-.,-.,-..---.  .--.   : .. :.-.,-.,-. .--.   .-' : .--.      |");
	puts("                                              |    : :__ ' .; ; : ,. ,. :: .; `' .; :  : :; :: :: ,. :' .; ; ' .; :' .; :     |");
	puts("                                              |    `.__.'`.__,_;:_;:_;:_;: ._.'`.__.'  :_;:_;:_;:_;:_;`.__,_;`.__.'`.__.'     |");
	puts("                                              |                          : :                                                  |");
	puts("                                              |                          :_;                                                  |");
	puts("                                              ---------------------------------------------------------------------------------");
	fflush(stdin);
    usleep(1000000);
    screenSetColor(WHITE, DARKGRAY);
    screenShowCursor();
} 

void you_win(){
    usleep(1000000);
    screenHideCursor();
	fflush(stdin);
    screenSetColor(GREEN, DARKGRAY);
	printf("\n\n");
	puts("");
	puts("                                              |-----------------------------------------------------------------------------|");
	puts("                                              | .--.   .--.             ^       .----.               ,-.                    |");
	puts("                                              | :  :   :  :            ^ ^     :  .--'               : :                    |");
	puts("                                              | :  :._.:  : .--. .---..---.    :  :  __  .--.  ,-.,-.: :,-. .--.  _   _     |");
	puts("                                              |  :        :' .; :: :: : :-'    :  :__:: ' .; ; : ,. :: :  :' .; :' '.; '    |");
	puts("                                              |   :..__..: `.__.'`.__,`.__;    `.____.' `.__,_;:_;:_;:_;:_;`.__.'`.___.'    |");
	puts("                                              |                                                                             |");
	puts("                                              |                                                                             |");
	puts("                                              |-----------------------------------------------------------------------------|");

    screenSetColor(YELLOW, DARKGRAY);
	printf("                                                                              ___________      \n");
	printf("                                                                             '._==_==_=_.'     \n");
	printf("                                                                             .-\\:      /-.    \n");
	printf("                                                                            | (|:.     |) |    \n");
	printf("                                                                             '-|:.     |-'     \n");
	printf("                                                                               \\::.    /      \n");
	printf("                                                                                '::. .'        \n");
	printf("                                                                                  ) (          \n");
	printf("                                                                                _.' '._        \n");
	printf("                                                                               '-------'       \n\n");
    screenSetColor(WHITE, DARKGRAY);
    usleep(2500000);
    screenShowCursor();
	fflush(stdin);	
}

void print_podium(Player *head) {
	Player *n = head;
    int count = 0;
    char winners [3][SIZE_NAME];
	int winners_score[3];

    for(int i = 0; i < 3; i++){
		strcpy(winners[i], "");
		winners_score[i] = 0;
	}

    while(n != NULL || count > 2){
        strncpy(winners[count], n->name, 10);
		winners[count][10] = '\0';
		winners_score[count] = n->score;
        n = n->next;
        count++;
    }

	screenSetColor(YELLOW, DARKGRAY);

    printf("\n\n");
    printf("  ********** PÓDIO DOS MELHORES JOGADORES **********\n\n");
    printf("                        1º Lugar\n");
    printf("                        _________\n");
    printf("                       |         |\n");
    printf("                       |%-10s|\n", winners[0]);
    printf("                       |  %4d   |\n", winners_score[0]);
    printf("                       |_________|\n");
    printf("     2º Lugar          |         |          3º Lugar\n");
    printf("     _________         |         |          _________\n");
    printf("    |         |        |         |         |         |\n");
    printf("    |%-10s|     |           |         |%-10s|\n", winners[1], winners[2]);
    printf("    |  %4d   |        |         |         |  %4d   |\n", winners_score[1], winners_score[2]);
    printf("    |_________|        |_________|         |_________|\n\n");
    printf("  *****************************************************\n");

	screenSetColor(WHITE, DARKGRAY);
}

void project_presentation(){
	screenSetColor(MAGENTA, DARKGRAY);

	printf("|-----------------------------------------------------------------------------|\n");
	printf("|                                  ALUNOS:                                    |\n");
	printf("|                             Igor Alves Almeida                              |\n");
	printf("|                            Lucas Barcelar Kabbaz                            |\n");
	printf("|                               Emanuel Eduardo                               |\n");
	printf("|                                                                             |\n");
	printf("|-----------------------------------------------------------------------------|\n");
	printf("|                               PROFESSORA                                    |\n");
	printf("|                              Pamela Thays                                   |\n");
	printf("|                              Tiaguinho Guedes                               |\n");
	printf("|                              CESAR SCHOOL                                   |\n");
	printf("|-----------------------------------------------------------------------------|\n");

	screenSetColor(WHITE, DARKGRAY);

	printf("\n\n\n\nPressione ENTER para continuar...");
	getchar();
}