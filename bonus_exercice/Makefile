CC=gcc
CFLAGS=-Wall -g -Wextra -Werror -std=c99 -pedantic

SRC= heap.c

OBJ=$(SRC:.c=.o)

all: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o test

clean:
	$(RM) $(OBJ)

