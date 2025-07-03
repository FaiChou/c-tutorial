CC=clang
CFLAGS=-g -Wall
BIN=example
OBJS=ppm.o example.o

.PHONY: all
all: $(BIN)

%.o: %.c
	$(CC) $(CFLAGS) -c $^

example: example.o $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: clean
clean:
	rm -f $(BIN) $(OBJS)