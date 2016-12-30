#include <stdio.h>
#include <stdlib.h>

#include "console.h"

void clear_console()
{
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
void render(char screen[WIN_H][WIN_W],int nblines)
{
    int i,j;
    for (i=0; i<WIN_H && i < nblines; i++)
    {
        for (j=0; j<WIN_W ; j++)
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

int clean_stdin()
{
    scanf ("%*[^\n]");
    getchar ();
    return 1;
}

char prompt_char()
{
    char buffer[2];
    scanf ("%1s", buffer);
    clean_stdin();
    return buffer[0];
}
int promptUINT()
{
    int n = 0;
    char c;
    do
    {
        printf("\n: ");

    } while (((scanf("%d%c", &n, &c)!=2 || c!='\n') && clean_stdin()) || n<1 );
    return n;
}
