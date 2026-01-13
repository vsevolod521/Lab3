CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2
TARGET = sort_program
SOURCES = main.c stack.c sorting.c functions.c 
OBJECTS = $(SOURCES:.c=.o) 

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

main.o: main.c stack.h sorting.h functions.h
	$(CC) $(CFLAGS) -c main.c

stack.o: stack.c stack.h
	$(CC) $(CFLAGS) -c stack.c

sorting.o: sorting.c sorting.h stack.h functions.h
	$(CC) $(CFLAGS) -c sorting.c

functions.o: functions.c functions.h 
	$(CC) $(CFLAGS) -c functions.c

clean:
	rm -f $(OBJECTS) $(TARGET) *.txt

.PHONY: all clean 
