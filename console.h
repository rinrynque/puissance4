#ifndef CONSOLE_H_INCLUDED
#define CONSOLE_H_INCLUDED

#define WIN_H 23
#define WIN_W 73

void clear_console();
void drawchar(char screen[WIN_H][WIN_W],int r, int c, char tile);
void render(char screen[WIN_H][WIN_W], int nblines); /* On veut juste afficher les lignes ou des choses sont ecrites */
void clear_screen(char screen[WIN_H][WIN_W]);

char prompt_char();
int promptUINT();

#endif /* CONSOLE_H_INCLUDED*/
