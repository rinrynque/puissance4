#include <stdio.h>
#include <stdlib.h>

#include "console.h"
/*
@requires: -
@assigns: -
@ensures: Ecrit de nombreux retours à la ligne pour faire disparaitre les ecritures dans la console
*/
void clear_console()
{
    printf("\n\n\n\n\n");
}

/*
@requires: un tableau de taille fixe représentant une image, des coordonnées et un caractère
@assigns: le tableau screen
@ensures: le caractere est ecrit au bon endroit si c'est dans le tableau
*/
void drawchar(char screen[WIN_H][WIN_W],const int r,const int c, const char tile)
{
    if(r>=0&&r<WIN_H&&c>=0&&c<WIN_W)
    {
        screen[r][c]=tile;
    }
}
/*
@requires: un tableau image un nombre de lignes
@assigns: -
@ensures: l'image est écrite dans la sortie
*/
void render(char screen[WIN_H][WIN_W],const unsigned int nblines)
{
    unsigned int i,j;
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
/*
@requires: un tableau à réinitialiser
@assigns: toutes les cases du tableau
@ensures: le tableau est rempli d'espaces
*/
void clear_screen(char screen[WIN_H][WIN_W])
{
    unsigned int i,j;
    for (i=0; i<WIN_H; i++)
    {
        for (j=0; j<WIN_W; j++)
        {
            screen[i][j]=' ';
        }
    }
    return;
}

/*
@requires: -
@assigns: -
@ensures: le flux stdin est vidé
*/
int clean_stdin()
{
    scanf ("%*[^\n]"); /* Regex vidant tous les caractères avant un \n*/
    getchar (); /* Vide le \n */
    return 1;
}
/*
@requires: -
@assigns: -
@ensures: retourne le premier caractère saisi par l'utilisateur et laisse stdin vide
*/
char prompt_char()
{
    char buffer[2];
    scanf ("%1s", buffer);
    clean_stdin();
    return buffer[0];
}
/*
@requires: -
@assigns: -
@ensures: retourne un entier saisi par l'utilisateur et laisse stdin vide
*/
unsigned int promptUInt()
{
    int n = 0;
    char c;
    do
    {
        printf("\n: ");

    } while (((scanf("%d%c", &n, &c)!=2 || c!='\n') && clean_stdin()) || n<1 ); /* On boucle sur la demande tant que l'utilisateur n'a pas rentré une saisie correcte (correspondante à l'expression du scanf)*/
    return n;
}
