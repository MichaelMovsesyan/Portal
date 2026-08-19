CC = gcc
CFLAGS = -Wall -Wextra -std=c11
LIBS = -lraylib -lX11 -lXrandr -lXi -lXcursor -lXinerama -lGL -lm

TARGET = main
SOURCES = main.c

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET) $(LIBS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: run clean