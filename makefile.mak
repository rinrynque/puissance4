CC=gcc
CFLAGS=-Wall -Wextra -ansi
LDFLAGS=
EXEC=puissance4.exe
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)

all: $(EXEC)

puissance4: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

pile.o: pile.h
console.o: console.h
jeu.o: jeu.h
main.o: jeu.h

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean mrproper

clean:
	rm -rf *.o 

mrproper: clean
	rm -rf $(EXEC)
	
cleancodeblocks: clean
	rm -rf $(EXEC) *.layout *.depend bin obj