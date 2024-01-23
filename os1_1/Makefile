CC=gcc
CFLAGS=-Wall

.PHONY: all clean run_without_debug run_with_debug run2_without_debug run2_with_debug

all: program_without_debug program_with_debug program2_without_debug program2_with_debug 

program_without_debug: program.c
	$(CC) $(CFLAGS) program.c -o program_without_debug

program_with_debug: program.c
	$(CC) -g $(CFLAGS) program.c -o program_with_debug

run_without_debug: program_without_debug
	./program_without_debug

run_with_debug: program_with_debug
	./program_with_debug

program2_without_debug: program2.c
	$(CC) $(CFLAGS) program2.c -o program2_without_debug

program2_with_debug: program2.c
	$(CC) -g $(CFLAGS) program2.c -o program2_with_debug

run2_without_debug: program2_without_debug
	./program2_without_debug

run2_with_debug: program2_with_debug
	./program2_with_debug

clean:
	rm -f program_without_debug program_with_debug program2_without_debug program2_with_debug

