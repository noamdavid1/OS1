CC = gcc
CFLAGS = -Wall
all: polyalphabetic

polyalphabetic: main.o polyalphabetic.o
	$(CC) $(CFLAGS) -o polyalphabetic main.o polyalphabetic.o

main.o: main.c polyalphabetic.h
	$(CC) $(CFLAGS) -c main.c

polyalphabetic.o: polyalphabetic.c polyalphabetic.h
	$(CC) $(CFLAGS) -c polyalphabetic.c

clean:
	rm -f polyalphabetic *.o
