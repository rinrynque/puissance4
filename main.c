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

    int tour = 0;
    while(j_turn(&jeu,tour%2+1)!=-1)
    {
        int check = 0;

        if(jeu.options & TRIDIM)
        {
            check = j_check3D(&jeu);
        }
        else
        {
            check = j_checkUp(&jeu);
        }

        if (check)
        {
            printf("Bien joue ! \nContinuer (o/n)?\n", check);
            char c = ' ';
            while(c != 'o')
            {
                c = prompt_char();
                if (c == 'n')
                {
                    return 0;
                }
            }
        }

        if(jeu.options & EARTHQUAKE)
        {
            j_earthQUAKE(&jeu);
            if(!(jeu.options & TRIDIM))
            {
                check = j_checkUp(&jeu);
                if (check)
                {
                    if (check==3)
                        printf("Deux gagnants ! Il n\'y aura pas de jaloux\n");
                    printf("Bien joue ! \nContinuer (o/n)?\n");
                    char c = ' ';
                    while(c != 'o')
                    {
                        c = prompt_char();
                        if (c == 'n')
                        {
                            return 0;
                        }
                    }
                }
            }
        }
        tour++;
    }
    printf("\n\nJoueur %d abandonne\nJoueur %d est vainqueur par forfait !\n\nAu revoir !\n",tour%2+1, (tour+1)%2+1);
    getchar();
    j_quit(&jeu);
    return 0;
}
