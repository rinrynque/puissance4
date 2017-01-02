#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "pile.h"
#include "jeu.h"

int main(int argc, char** argv)
{
    printf("=======================\n");
    printf("=Bienvenue dans le Jeu=\n"); /* J'ai perdu */
    printf("=======================\n");
    printf("Vianney TOUCHARD (tm)\n");

    srand((unsigned)time(NULL));
    rand();rand();rand();rand(); /* Solution pragmatique : sans cette ligne, les rand() renvoyaient des résultats très similaires lors de différentes exécutions */
    getchar(); /* On utilise des getchar pour faire des pauses */

    int n=0;
    printf(" Choisissez la taille du plateau");
    n = promptUInt();
    if( n*3 + 5>WIN_H || n*3 + 5 > WIN_W)
    {
        printf("Attention ! La taille choisie est trop grande pour l\'affichage\n");
        printf("Le plateau risque de ne pas etre entierement visible\nsans modification des macros de preprocesseur\n\n");
    }

    /** Menus de sélection des options **/
    int choix = 0;
    {
        char c = ' ';
        while(c != '1' && c != '2')
        {
            printf("Quelle variante souhaitez-vous jouer?\nVariante vue de dessus : 1\nVariante 3D : 2\n");
            c = prompt_char();
            if (c=='q') /* Pour quitter immédiatement */
                return 0;
        }
        if(c=='2')
            choix |= TRIDIM;

        c = ' ';
        while(c != 'o' && c != 'n')
        {
            printf("Voulez-vous activer l\'option SEISME (o/n)?\n");
            c = prompt_char();
            if (c=='q')
                return 0;
        }
        if(c=='o')
            choix |= EARTHQUAKE;

    }

    /** On crée une structure jeu et on l'initialise **/
    s_jeu jeu;
    j_init(&jeu,n, choix);

    int tour = 0;
    while(j_turn(&jeu,tour%2+1)!=-1) /* j_turn renvoie -1 si le joueur décide de quitter, on utilise un modulo pour alterner les joueurs */
    {
        int check = 0;

        /** Vérification de victoire : dépend de la variante choisie **/
        if(jeu.options & TRIDIM)
        {
            check = j_check3D(&jeu);
        }
        else
        {
            check = j_checkUp(&jeu);
        }

        /* On termine le programme si la vérification a détecté un vainqueur */
        if (check) /* Car if(check) est équivalent à if(check != 0) */
        {
            printf("Bien joue ! \nContinuer (o/n)?\n");
            char c = ' ';
            while(c != 'o')
            {
                c = prompt_char();
                if (c == 'n')
                {
                    j_quit(&jeu); /* On libère la mémoire et on quitte */
                    return 0;
                }
            }
        }

        /** Gestion de l'option seisme **/
        if(jeu.options & EARTHQUAKE) /* Si l'option seisme est activée */
        {
            j_earthQUAKE(&jeu); /* On applique les regles du seisme */
            if(!(jeu.options & TRIDIM)) /* Si la variante est la vue de dessus, le seisme peut avoir entraine une victoire */
            {
                check = j_checkUp(&jeu); /* On reverifie en variante de dessus */
                if (check)
                {
                    if (check==3) /* Il peut y avoir deux vainqueurs */
                        printf("Deux gagnants ! Il n\'y aura pas de jaloux\n");
                    printf("Bien joue ! \nContinuer (o/n)?\n");
                    char c = ' ';
                    while(c != 'o')
                    {
                        c = prompt_char();
                        if (c == 'n')
                        {
                            j_quit(&jeu); /* On libère la mémoire et on quitte */
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
    j_quit(&jeu); /* On libère la mémoire (destruction de la structure) */
    return 0;
}
