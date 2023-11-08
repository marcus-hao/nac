EXEC = nac.out
SOURCES = $(wildcard src/*.c)
OBJECTS = $(SOURCES:.c=.o)
CC = gcc
FLAGS = -g -Wall -lm -ldl -fPIC -rdynamic

$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) $(FLAGS) -o $(EXEC)

%.o: %.c include/%.h
	$(CC) -c $(FLAGS) $< -o $@

clean:
	-rm *.out
	-rm src/*.o
