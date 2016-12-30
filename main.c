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

    j_init(&jeu,5, TRIDIM);

    int tour = 0;
    while(j_turn(&jeu,tour%2+1)!=-1)
    {
        if(jeu.options & EARTHQUAKE)
        {
            j_earthQUAKE(&jeu);
        }

        if(jeu.options & TRIDIM)
        {
            int check = j_check3D(&jeu);
            if(check)
            {
                printf("Le joueur %d gagne !\n", check);
                getchar();
                j_quit(&jeu);
                return 0;
            }
        }
        else
        {
            j_checkUp(&jeu);
        }
        tour++;
    }
    printf("\n\nAu revoir !\n\nJoueur %d abandonne\nJoueur %d est vainqueur par forfait !\n",tour%2+1, (tour+1)%2+1);
    getchar();
    j_quit(&jeu);
    return 0;
}
