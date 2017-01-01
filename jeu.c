#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "jeu.h"

const char TILES[3] = " ox";

/*
@requires: i et n des entiers
@assigns: -
@ensures: retourne le résultat mathématiquement correct de l'operation i modulo n
*/
int positive_modulo(int i, unsigned int n)
{
    return (i % n + n) % n;
}

/* Jeu* signifie "pointeur vers une structure de type s_jeu" */
/*
@requires: un Jeu* jeu , n la taille du plateau voulu, les flags options des options voulues
@assigns: les attributs de *jeu
@ensures: *jeu est initialisé
*/
void j_init(s_jeu* jeu, unsigned int n, unsigned int options)
{
    unsigned int i,j;
    jeu->options = options;
    jeu->n = n;
    jeu->board = (Pile**) malloc(n * sizeof(Pile*));
    jeu->events = (int**) malloc(n * sizeof(int*));
    for (i=0; i<n; i++)
    {
        jeu->board[i] = (Pile *)malloc(n * sizeof(Pile));
        jeu->events[i] = (int*)malloc(n * sizeof(int));
        for (j=0; j<n; j++)
        {
            jeu->events[i][j]=0;
            p_init(&(jeu->board[i][j]));
        }
    }
    clear_screen(jeu->screen);
}

/*
@requires: un Jeu*
@assigns: jeu->board
@ensures: libère la mémoire allouée pour jeu->board
*/
void j_quit(s_jeu* jeu)
{
    int i;
    for (i=0; i<jeu->n; i++)
    {
        free(jeu->board[i]);
        jeu->board[i] = NULL;
    }
    free(jeu->board);
    jeu->board = NULL;
}

/*
@requires: un Jeu* jeu
@assigns: jeu->screen (par drawchar)
@ensures: le terrain est dessiné dans le tableau jeu->screen pour un affichage ultérieur
*/
void j_draw_board(s_jeu* jeu)
{
    int i,j;
    for(i=0;i<jeu->n;i++)
    {
        for(j=0;j<jeu->n;j++)
        {
            if( !p_isEmpty(&(jeu->board[i][j])) )
            {
                drawchar(jeu->screen,i*3+1,j*3+1, TILES[p_peak(&((jeu->board)[i][j]))]);
            }
        }
    }
    /*On dessine aussi la petite ligne de kéké en dessous*/
    for(i=0;i<jeu->n*3;i++)
        drawchar(jeu->screen,jeu->n*3, i, '-');
}

/*
@requires: un Jeu* jeu, r (ligne), c (colonne) les coordonnées de la pile que l'on veut afficher
@assigns: jeu->screen (par drawchar)
@ensures: la pile aux coordonnées r,c  est dessinée dans le tableau jeu->screen pour un affichage ultérieur
*/
void j_draw_pile(s_jeu* jeu, const int r, const int c)
{
    Pile* p = &(jeu->board[r][c]);
    int i;
    int x = jeu->n*3+1; /*x et y sont les coordonnees d affichage de la pile (bas gauche)*/
    int y = jeu->n*3;
    for(i=0;i<3;i++)
        drawchar(jeu->screen,y,x+i, '-');

    for(i=0; i<p->it; i++)
    {
        drawchar(jeu->screen,y-i-1,x+1,TILES[p->tab[i]]);
    }
}
/*
@requires: un Jeu* jeu
@assigns: jeu->screen (par drawchar) ( et jeu->events (retrait du flag ALIGNED (déboguage)) )
@ensures: les événements indiqués dans jeu->events sont dessinés dans le tableau jeu->screen pour un affichage ultérieur
*/
void j_draw_events(s_jeu* jeu)
{
    int i,j;
    for(i=0;i<jeu->n;i++)
    {
        for(j=0;j<jeu->n;j++)
        {
            if(jeu->events[i][j] & COLLAPSED) /* Si le flag COLLAPSED est activé sur la case */
            {

                drawchar(jeu->screen, i*3, j*3,   '*');
                drawchar(jeu->screen, i*3, j*3+1, '*');
                drawchar(jeu->screen, i*3, j*3+2, '*');

                drawchar(jeu->screen, i*3+1, j*3,   '*');
                drawchar(jeu->screen, i*3+1, j*3+2, '*');

                drawchar(jeu->screen, i*3+2,   j*3, '*');
                drawchar(jeu->screen, i*3+2, j*3+1, '*');
                drawchar(jeu->screen, i*3+2, j*3+2, '*');
            }
            if(jeu->events[i][j] & ALIGNED) /* Si le flag ALIGNED est activé sur la case */
            {
                drawchar(jeu->screen, i*3+1, j*3+1,   '@');
                jeu->events[i][j] &= ~ALIGNED;
            }
        }
    }
}

/*
@requires: un Jeu* jeu, r et c les coordonnées du curseur
@assigns: jeu->screen (par drawchar)
@ensures: un curseur est dessiné dans le tableau jeu->screen pour un affichage ultérieur
*/
void j_draw_cursor(s_jeu* jeu,int r, int c)
{
        drawchar(jeu->screen, r*3,   c*3+1, '+');
        drawchar(jeu->screen, r*3+1, c*3,   '+');
        drawchar(jeu->screen, r*3+1, c*3+2, '+');
        drawchar(jeu->screen, r*3+2, c*3+1, '+');
}

/*
@requires: un Jeu* jeu, un entier player indiquant le joueur dont c'est le tour
@assigns: jeu->screen (appels aux fonctions d'affichage), jeu->events (pour mettre à jour les emplacements joués
          jeu->board (pose/retrait de pièces)
@ensures: assure l'interaction avec le joueur et applique la décision choisie pour le tour
*/
int j_turn(s_jeu* jeu, const int player)
{
    char in = ' ';
    int r = 0,c = 0;
    int fallout = FALLOUT_TIME;
    while(1)
    {
        clear_console();
        clear_screen(jeu->screen);
        j_draw_board(jeu);
        j_draw_pile(jeu,r,c);

        if (fallout != 0)
        {
            j_draw_events(jeu);
            fallout--;
        }

        j_draw_cursor(jeu,r,c);
        render(jeu->screen, jeu->n*3+2);

        printf("C'est au tour du joueur %d (joue les %c) (h : afficher les commandes)\n", player, TILES[player]);
        in = prompt_char();
        if(in=='p')
        {
            p_push(&(jeu->board[r][c]),player);
            jeu->events[r][c] |= PLAYED;
            return 1;
        }
        else if(in=='r')
        {
            if(p_isEmpty(&(jeu->board[r][c])))
            {
                printf("La pile est deja vide, vous ne pouvez rien retirer\n");
                getchar(); /*Pour faire une pause*/
            }
            else
            {
                p_pop(&(jeu->board[r][c]));
                jeu->events[r][c] |= PLAYED; /*On ajoute sur la case le flag PLAYED */
                return 0;
            }
        }
        else if(in=='i')
        {
            r--;
        }
        else if(in=='k')
        {
            r++;
        }
        else if(in=='j')
        {
            c--;
        }
        else if(in=='l')
        {
            c++;
        }
        else if(in=='h')
        {
            printf("\n");
            printf("   ^   \n");
            printf("   i   \n");
            printf("<j   l>\n");
            printf("   k   \n");
            printf("   v   \n");
            printf("\n");
            printf("p : poser un jeton\n");
            printf("r : retirer un jeton\n");
            printf("q : quitter :-(\n\n\n");
            getchar();
        }
        else if(in=='q')
        {
            return -1;
        }
        r = positive_modulo(r, jeu->n);
        c = positive_modulo(c, jeu->n);
    }
}

/*
@requires: un Jeu* jeu
@assigns: jeu->board (pour mettre à jour les piles écroulées) jeu->events pour marquer les piles ecroulées
@ensures: applique les règles d'ecroulement de l'option seisme au plateau de jeu
*/
void j_earthQUAKE(s_jeu* jeu)
{
    int i,j;
    for(i=0;i<jeu->n;i++)
    {
        for(j=0;j<jeu->n;j++)
        {
            jeu->events[i][j] &= ~COLLAPSED; /* Cette ligne permet de remettre le flag COLLAPSED à 0*/
            int h = jeu->board[i][j].it;
            if(h>0 && (rand()/(double)RAND_MAX) < 1.0-pow(2.0,-h/(2.0*jeu->n)))
            {
                /*Effondrement*/
                jeu->events[i][j] |= COLLAPSED; /* Cette ligne permet de mettre le flag COLLAPSED à 1*/
                int k = rand()%h+1;
                int ip;
                for(ip = 0; ip<k;ip++)
                {
                    p_pop(&(jeu->board[i][j]));
                }
                printf("Une pile s'est effondree de %d etages!\n",k);
                getchar(); /*Pour faire une pause*/
            }
        }
    }
}

/*
@requires: un Jeu* jeu, x,y,z des coordonnées sur le plateau, dx,dy,dz le deplacement sur les trois axes, piece le type de pièce à observer
@assigns: -
@ensures: retourne le nombre de pièces du type piece alignées à partir de (x,y,z) non inclus dans la direction indiquée par le vecteur (dx,dy,dz)
*/
int j_follow3D(s_jeu* jeu, const int xi, const int yi, const int zi, const int dx, const int dy, const int dz, const int piece)
{
    int length = 0;
    int x = xi + dx;
    int y = yi + dy;
    int z = zi + dz;

    while(x>=0 && y>=0 && z>=0
          && x<jeu->n && y<jeu->n
          && z < jeu->board[x][y].it
          && (jeu->board[x][y]).tab[z] == piece)
    {
        length++;
        x += dx;
        y += dy;
        z += dz;
    }
    return length;
}

/*
@requires: un Jeu* jeu
@assigns: jeu->events, jeu->screen
@ensures: vérifie si les conditions de victoire selon la variante 3D sont remplies par l'un ou l'autre des joueurs et retourne le résultat
*/
int j_check3D(s_jeu* jeu)
{
    int i,j;
    const int dxs[9]={1, 1, 0, -1, 0, 1, 1, 0, -1};
    const int dys[9]={0, 1, 1, 1,  0, 0, 1, 1,  1};
    const int dzs[9]={0, 0, 0, 0,  1, 1, 1, 1,  1};
    for(i=0;i<jeu->n;i++)
    {
        for(j=0;j<jeu->n;j++)
        {
            if(jeu->events[i][j] & PLAYED) /* Si le flag PLAYED est activé sur la case */
            {
                /*On doit partir dans 9 directions différentes, a chaque fois des deux côtés */

                if(!p_isEmpty(&(jeu->board[i][j])))
                {
                    int player = p_peak(&(jeu->board[i][j]));
                    int k;
                    for(k=0;k<9;k++)
                    {
                        int align = j_follow3D(jeu,i,j,jeu->board[i][j].it-1,dxs[k],dys[k], dzs[k], player)
                                    + 1 + j_follow3D(jeu,i,j,jeu->board[i][j].it-1,-dxs[k],-dys[k],-dzs[k], player);
                        if(align >= jeu->n)
                        {
                            clear_console();
                            clear_screen(jeu->screen);
                            j_draw_board(jeu);
                            j_draw_events(jeu);
                            render(jeu->screen, jeu->n*3+2);

                            printf("Le joueur %d gagne !\n", player);
                            getchar();
                            return player;
                        }
                    }
                }

                jeu->events[i][j] &= ~PLAYED; /* On a fait la verification, on enleve le flag */
            }
        }
    }
    return 0; /* Il n'y a pas de vainqueur */
}

/*Les fonctions de verification de victoire en variante vue de dessus sont les mêmes que celles pour la variante 3d à quelques details pres*/

/*
@requires: un Jeu* jeu, x,y des coordonnées sur le plateau, dx,dy le deplacement sur les deux axes, piece le type de pièce à observer
@assigns: -
@ensures: retourne le nombre de pièces du type piece alignées sur le dessus des piles à partir de la pile en (x,y) non inclus dans la direction indiquée par le vecteur (dx,dy)
*/
int j_followUp(s_jeu* jeu, int x, int y, int dx, int dy, int piece)
{
    int length = 0;
    x += dx;
    y += dy;

    while(x>=0 && y>=0
          && x<jeu->n && y<jeu->n
          && !p_isEmpty(&(jeu->board[x][y]))
          && p_peak(&(jeu->board[x][y])) == piece)
    {
        length++;
        x += dx;
        y += dy;
    }
    return length;
}

/*
@requires: un Jeu* jeu
@assigns: jeu->events, jeu->screen
@ensures: vérifie si les conditions de victoire selon la variante vue de dessus sont remplies par l'un ou l'autre des joueurs et retourne le résultat
*/
int j_checkUp(s_jeu* jeu)
{
    int i,j;
    const int dxs[4]={1, 1, 0, -1};
    const int dys[4]={0, 1, 1, 1};

    int etat = 0;

    for(i=0;i<jeu->n;i++)
    {
        for(j=0;j<jeu->n;j++)
        {
            if(jeu->events[i][j] & PLAYED || jeu->events[i][j] & COLLAPSED) /* Si le flag PLAYED ou le flag COLLAPSED est activé sur la case */
            {
                /*On doit partir dans 4 directions différentes, a chaque fois des deux côtés */

                if(!p_isEmpty(&(jeu->board[i][j])))
                {
                    int player = p_peak(&(jeu->board[i][j]));
                    int k;
                    for(k=0;k<4;k++)
                    {
                        int align = j_followUp(jeu,i,j,dxs[k],dys[k], player)
                                    + 1 + j_followUp(jeu,i,j,-dxs[k],-dys[k], player); /* On ajoute 1 pour prendre en compte la case courante*/


                        if(align >= jeu->n)
                        {
                            clear_console();
                            clear_screen(jeu->screen);
                            j_draw_board(jeu);
                            render(jeu->screen, jeu->n*3+2);
                            printf("Le joueur %d gagne !\n", player);
                            getchar();
                            if (etat==0)
                            {
                                etat = player;
                            }
                            else if (etat != player)
                            {
                                etat = 3;
                            }
                        }
                    }
                }

                jeu->events[i][j] &= ~PLAYED; /* On a fait la verification, on enleve le flag */
            }
        }
    }
    return etat;
}
