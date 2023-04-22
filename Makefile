CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC = main.c
OBJ = $(SRC:.c=.o)
TEST_DIR = tests
TESTS = $(wildcard $(TEST_DIR)/*.txt)
EXEC = a.out

.PHONY: all clean test

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)

test: $(EXEC)
	@for t in $(TESTS); do \
		echo "Running test $$t"; \
		./$(EXEC) < $$t; \
	done

