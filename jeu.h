#ifndef JEU_H_INCLUDED
#define JEU_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "console.h"
#include "pile.h"

#define NOTHING 0
#define EARTHQUAKE 1
#define TRIDIM 2 /*Si ce flag n'est pas active, on utilise la variante vue de dessus*/

/*Fonctions pratiques*/
int positive_modulo(int i, int n);

/*Jeu*/
struct s_jeu
{
    int n; /*taille du plateau*/
    Pile **board; /*plateau de jeu*/
    int **collapses; /*la carte des effondrements*/
    char screen[WIN_H][WIN_W]; /*l'ecran de rendu*/
    unsigned int options; /*les options sont representes par les flags*/
};

typedef struct s_jeu s_jeu;

void j_init(s_jeu* jeu, int n, unsigned int options);
void j_quit(s_jeu* jeu);
void j_draw_board(s_jeu* jeu);
int j_turn(s_jeu* jeu, int player);

int j_check3D(s_jeu* jeu);
int j_checkUp(s_jeu* jeu);

void j_earthQUAKE(s_jeu* jeu);

#endif // JEU_H_INCLUDED
