EXEC = nac.out
SOURCES = $(wildcard src/*.c)
OBJECTS = $(SOURCES:.c=.o)
CC = gcc
FLAGS = -g -Wall -lm -ldl -fPIC -rdynamic

$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) $(FLAGS) -o $(EXEC)

%.o: %.c include/%.h
	$(CC) -c $(FLAGS) $< -o $@

EXAMPLES = $(wildcard examples/*.nac)
SORTED_EXAMPLES = $(sort $(EXAMPLES))

test: $(EXEC)
	for example in $(SORTED_EXAMPLES); do \
		echo "\nTesting $$example"; \
		./$(EXEC) $$example; \
		echo "\nDone with $$example\n"; \
	done

clean:
	-rm *.out
	-rm src/*.o