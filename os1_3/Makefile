CC = gcc
CFLAGS = -Wall 

SRC_FILES = main.c polyalphabetic.c 
HEADER_FILES = polyalphabetic.h 
OBJ_FILES = $(SRC_FILES:.c=.o)


all: program

program: $(OBJ_FILES)
	$(CC) $(CFLAGS) $(OBJ_FILES) -o program

clean:
	rm -f $(OBJ_FILES) program

.PHONY: all clean
			