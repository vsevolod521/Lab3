CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2
TARGET = sort_program
SOURCES = main.c stack.c sorting.c
OBJECTS = $(SOURCES:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

main.o: main.c stack.h sorting.h
	$(CC) $(CFLAGS) -c main.c

stack.o: stack.c stack.h
	$(CC) $(CFLAGS) -c stack.c

sorting.o: sorting.c sorting.h stack.h
	$(CC) $(CFLAGS) -c sorting.c

clean:
	rm -f $(OBJECTS) $(TARGET) *.txt

run: $(TARGET)
	./$(TARGET)

test_with_file: $(TARGET)
	./$(TARGET) -file input.txt

benchmark: $(TARGET)
	./$(TARGET)

.PHONY: all clean run test_with_file benchmark