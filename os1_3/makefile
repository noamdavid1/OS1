CC = gcc
CFLAGS = -Wall 

SRC_FILES = main.c polyalphabetic.c 
HEADER_FILES = polyalphabetic.h 
OBJ_FILES = $(SRC_FILES:.c=.o)

TARGET = encriptor

all: $(TARGET)

%.o: %.c $(HEADER_FILES)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) $(OBJ_FILES) -o $(TARGET)

clean:
	rm -f $(OBJ_FILES) $(TARGET)

.PHONY: all clean
			