#ifndef JEU_H_INCLUDED
#define JEU_H_INCLUDED

#define WIN_H 20
#define WIN_W 70

void clear_console();
void render(char screen[WIN_H][WIN_W]);
void clear_screen(char screen[WIN_H][WIN_W]);

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

#endif // JEU_H_INCLUDED
