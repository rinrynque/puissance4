#include <stdio.h>
#include <stdlib.h>

#include "pile.h"
#include "jeu.h"

const char TILES[2] = {' ','o','x'};

void clear_console()
{
    int i;
    for(i=0; i<200; i++)
    {
        printf("\n");
    }
}

void render(char screen[WIN_H][WIN_W])
{
    int i,j;
    for (i=0; i<WIN_H; i++)
    {
        for (j=0; j<WIN_W; j++)
        {
            printf("%c", screen[i][j]);
        }
        printf("\n");
    }
    return;
}

void clear_screen(char screen[WIN_H][WIN_W])
{
    int i,j;
    for (i=0; i<WIN_H; i++)
    {
        for (j=0; j<WIN_W; j++)
        {
            screen[i][j]=' ';
        }
    }
    return;
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
                jeu->screen[i*3+1][j*3+1] = TILES[p_peak(&((jeu->board)[i][j]))];
            }
        }
    }
    clear_console();
    render(jeu->screen);
    clear_screen(jeu->screen);
}
