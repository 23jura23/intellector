.PHONY: all build debug release fsanitize test test_fsanitize clean

CXX = g++

CFLAGS = --std=c++17 -Wall -Wextra -Wshadow
INC = -Iinclude
EXTRA_FLAGS =

DEBUG_FLAGS = -g
RELEASE_FLAGS = -Ofast
FS_FLAGS = ${DEBUG_FLAGS} -fsanitize=address
LINK_FLAGS = -lncurses

FILES = $(shell ls src)
SRCS = $(FILES:%.cpp=src/%.cpp)
OBJS = $(FILES:%.cpp=obj/%.o)
DEP = $(OBJS:%.o=%.d)
BIN = intellector

TEST_FILES = $(subst main.cpp,,$(shell ls src) $(shell ls test))
TEST_SRCS = $(TEST_FILES:%.cpp=test/%.cpp)
TEST_OBJS = $(TEST_FILES:%.cpp=obj/%.o)
TEST_DEP = $(TEST_OBJS:%.o=%.d)
TEST_BIN = test_${BIN}

all: release
build: bin/${BIN}

debug: EXTRA_FLAGS += ${DEBUG_FLAGS}
debug: build

release: EXTRA_FLAGS += ${RELEASE_FLAGS}
release: build

fsanitize: EXTRA_FLAGS += ${FS_FLAGS}
fsanitize: build

clang: CXX = clang++
clang: EXTRA_FLAGS += -Wno-c++98-compat -Wno-c++-compat -Wno-padded
clang: build

clang_everything: CXX = clang++
clang_everything: EXTRA_FLAGS += -Weverything -Wno-c++98-compat -Wno-c++-compat -Wno-padded
clang_everything: build

test: bin/${TEST_BIN}
	./bin/${TEST_BIN}

test_fsanitize: EXTRA_FLAGS += ${FS_FLAGS}
test_fsanitize: test

bin/${BIN}: ${OBJS} | obj bin
	${CXX} ${CFLAGS} ${EXTRA_FLAGS} ${OBJS} ${LINK_FLAGS} -o bin/${BIN}

bin/${TEST_BIN}: ${TEST_OBJS} | obj bin
	${CXX} ${CFLAGS} ${EXTRA_FLAGS} ${TEST_OBJS} ${LINK_FLAGS} -o bin/${TEST_BIN}

-include ${DEP}
-include ${TEST_DEP}

obj/%.o: src/%.cpp | obj
	${CXX} ${CFLAGS} ${EXTRA_FLAGS} ${INC} ${LINK_FLAGS} -MMD -c $< -o $@

obj/%.o: test/%.cpp | obj
	${CXX} ${CFLAGS} ${EXTRA_FLAGS} ${INC} ${LINK_FLAGS} -MMD -c $< -o $@

obj:
	mkdir obj

bin:
	mkdir bin

clean:
	rm -rf obj bin error.txt

