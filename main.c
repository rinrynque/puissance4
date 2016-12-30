#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "pile.h"
#include "jeu.h"



int main()
{
    srand((unsigned)time(NULL));
    rand();rand();rand();rand();

    s_jeu jeu;
    j_init(&jeu,5, EARTHQUAKE);

    p_push(&(jeu.board[2][1]),1);
    int tour = 0;
    while(j_turn(&jeu,tour%2+1)!=-1)
    {
        if(jeu.options | EARTHQUAKE)
        {
            j_earthQUAKE(&jeu);
        }
        tour++;
    }

    j_quit(&jeu);
    return 0;
}
