#ifndef JEU_H_INCLUDED
#define JEU_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include "console.h"
#include "pile.h"

/*Fonctions pratiques*/
int positive_modulo(int i, int n);

/*Jeu*/
struct s_jeu
{
    int n; /*taille du plateau*/
    Pile **board; /*plateau de jeu*/
    char screen[WIN_H][WIN_W]; /*l'ecran de rendu*/
};

typedef struct s_jeu s_jeu;

void j_init(s_jeu* jeu, int n);
void j_quit(s_jeu* jeu);
void j_draw_board(s_jeu* jeu);
int j_tour(s_jeu* jeu, int player);

#endif // JEU_H_INCLUDED
