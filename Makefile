
SRC := $(wildcard src/*.c)
OBJ := $(patsubst src/%.c,obj/%.o,$(SRC))
TEST_SRC := $(wildcard test/*.c)

.DEFAULT: bin/postfix
.PHONY: all test

all: bin/postfix

test: bin/test

$(OBJ): obj/%.o: src/%.c
	gcc -c -o $@ $< -Iinclude


bin/postfix: $(OBJ)
	gcc -o $@ $^

bin/test: $(TEST_SRC) $(filter-out obj/main.o, $(OBJ))
	gcc -o $@ $^ -Iinclude 
