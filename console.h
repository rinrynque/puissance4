#ifndef CONSOLE_H_INCLUDED
#define CONSOLE_H_INCLUDED

#define WIN_H 20
#define WIN_W 70

void clear_console();
void drawchar(char screen[WIN_H][WIN_W],int r, int c, char tile);
void render(char screen[WIN_H][WIN_W]);
void clear_screen(char screen[WIN_H][WIN_W]);

char prompt_char();

#endif // CONSOLE_H_INCLUDED
