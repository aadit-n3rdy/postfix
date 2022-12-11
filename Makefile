
SRC_CPP := $(wildcard src/*.cpp)
SRC_C := $(wildcard src/*.c)
OBJ_C := $(patsubst src/%.c,obj/%.o,$(SRC_C))
OBJ_CPP := $(patsubst src/%.cpp,obj/%.o,$(SRC_CPP)) 
TEST_SRC := $(wildcard test/*.cpp)

OBJ := $(OBJ_CPP) $(OBJ_C)

.DEFAULT: bin/postfix
.PHONY: all test

all: bin/postfix

test: bin/test

$(OBJ_CPP): obj/%.o: src/%.cpp
	g++ -c -o $@ $< -Iinclude

$(OBJ_C): obj/%.o: src/%.c
	gcc -c -o $@ $< -Iinclude

bin/postfix: $(OBJ)
	g++ -o $@ $^

bin/test: $(TEST_SRC) $(filter-out obj/main.o, $(OBJ))
	g++ -o $@ $^ -Iinclude 
