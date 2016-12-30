#include "jeu.h"

const char TILES[3] = " ox";

int positive_modulo(int i, int n)
{
    return (i % n + n) % n;
}

void j_init(s_jeu* jeu, int n, unsigned int options)
{
    int i,j;
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

void j_draw_pile(s_jeu* jeu, int r, int c)
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
void j_draw_cursor(s_jeu* jeu,int r, int c)
{
        drawchar(jeu->screen, r*3,   c*3+1, '+');
        drawchar(jeu->screen, r*3+1, c*3,   '+');
        drawchar(jeu->screen, r*3+1, c*3+2, '+');
        drawchar(jeu->screen, r*3+2, c*3+1, '+');
}

int j_turn(s_jeu* jeu, int player)
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

int j_follow3D(s_jeu* jeu, int x, int y, int z, int dx, int dy, int dz, int piece)
{
    int length = 0;
    x += dx;
    y += dy;
    z += dz;

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
