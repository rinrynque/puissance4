#include <stdio.h>
#include <stdlib.h>

#include "pile.h"
#include "jeu.h"



int main()
{
    int i,j;
    s_jeu jeu;
    j_init(&jeu,5);
    p_push(&(jeu.board[2][1]),1);
    j_draw_board(&jeu);
    j_quit(&jeu);
    return 0;
}
