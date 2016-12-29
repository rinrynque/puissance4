#include <stdio.h>
#include <stdlib.h>

#include "console.h"

void clear_console()
{
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

void drawchar(char screen[WIN_H][WIN_W],int r, int c, char tile)
{
    if(r>=0&&r<WIN_H&&c>=0&&c<WIN_W)
    {
        screen[r][c]=tile;
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

char prompt_char()
{
    char buffer[2];
    scanf ("%1s", buffer);
    scanf ("%*[^\n]");
    getchar ();
    return buffer[0];
}
