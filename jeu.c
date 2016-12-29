#include "jeu.h"

const char TILES[2] = {' ','o','x'};

int positive_modulo(int i, int n)
{
    return (i % n + n) % n;
}

void j_init(s_jeu* jeu, int n)
{
    int i,j;
    jeu->n = n;
    jeu->board = (Pile**) malloc(n * sizeof(Pile*));
    for (i=0; i<n; i++)
    {
        jeu->board[i] = (Pile *)malloc(n * sizeof(Pile));
        for (j=0; j<n; j++)
        {
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
    for(i=0;i<3;i++)
        drawchar(jeu->screen,jeu->n*3,WIN_W-4+i, '-');

    for(i=0; i<p->it; i++)
    {
        drawchar(jeu->screen,jeu->n*3-i-1,WIN_W-3,TILES[p->tab[i]]);
    }
}

int j_tour(s_jeu* jeu, int player)
{
    char in = ' ';
    int r = 0,c = 0;
    while(1)
    {
        clear_console();
        clear_screen(jeu->screen);
        /*
        On dessine un curseur autour de la pile selectionnee, il y a 4 '+' à ecrire
        */
        drawchar(jeu->screen, r*3,   c*3+1, '+');
        drawchar(jeu->screen, r*3+1, c*3,   '+');
        drawchar(jeu->screen, r*3+1, c*3+2, '+');
        drawchar(jeu->screen, r*3+2, c*3+1, '+');
        j_draw_board(jeu);
        j_draw_pile(jeu,r,c);
        render(jeu->screen);

        printf("C'est au tour du joueur %d\n", player);
        in = prompt_char();
        if(in=='p')
        {
            p_push(&(jeu->board[r][c]),player);
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
        else if(in=='q')
        {
            return -1;
        }
        r = positive_modulo(r, jeu->n);
        c = positive_modulo(c, jeu->n);
    }
}
