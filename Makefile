# Compiler
CC = gcc

# Executable
TARGET = main

# Sources
SRC = main.c portal.c
OBJ = $(SRC:.c=.o)

# Compiler flags
CFLAGS = -Wall -Wextra -std=c17 -g

# Raylib and system libraries
LDLIBS = -lraylib -lm -ldl -lpthread -lrt -lX11 -lXrandr -lXi -lXcursor -lXinerama -lGL

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDLIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)

rebuild: clean all

.PHONY: all run clean rebuild