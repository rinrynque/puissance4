CC=gcc
CFLAGS=-Wall -Wextra -ansi
LDFLAGS=
EXEC=puissance4
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)

all: $(EXEC)

run:$(EXEC)
	./puissance4

puissance4: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean mrproper

clean:
	rm -rf *.o 

mrproper: clean
	rm -rf $(EXEC)
	
cleancodeblocks: clean
	rm -rf $(EXEC) *.layout *.depend bin obj