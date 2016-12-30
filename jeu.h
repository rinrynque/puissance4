#ifndef JEU_H_INCLUDED
#define JEU_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "console.h"
#include "pile.h"

#define FALLOUT_TIME 4 /*-1 pour afficher durant tout le tour les effondrements, 0 pour desactiver l'affichage*/

/*Définition des flags*/
#define NOTHING 0
#define EARTHQUAKE 1
#define TRIDIM 2 /*Si ce flag n'est pas active, on utilise la variante vue de dessus*/

#define COLLAPSED 1
#define PLAYED 2
#define ALIGNED 4 /* Ce flag a servi a des fins de debuggage */

/*Fonctions pratiques*/
int positive_modulo(int i, int n);

/*Jeu*/
struct s_jeu
{
    int n; /*taille du plateau*/
    Pile **board; /*plateau de jeu*/
    int **events; /*la carte des effondrements*/
    char screen[WIN_H][WIN_W]; /*l'ecran de rendu*/
    unsigned int options; /*les options sont representes par les flags*/
};

typedef struct s_jeu s_jeu;

void j_init(s_jeu* jeu, int n, unsigned int options);
void j_quit(s_jeu* jeu);
void j_draw_board(s_jeu* jeu);
int j_turn(s_jeu* jeu, int player);

int j_follow3D(s_jeu* jeu, int x, int y, int z, int dx, int dy, int dz, int piece);
int j_check3D(s_jeu* jeu);

int j_followUp(s_jeu* jeu, int x, int y, int dx, int dy, int piece);
int j_checkUp(s_jeu* jeu);

void j_earthQUAKE(s_jeu* jeu);

#endif // JEU_H_INCLUDED
