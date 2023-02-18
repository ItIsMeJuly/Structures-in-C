ASSIGNMENT=mystack
ASSIGNMENT_TEST=$(ASSIGNMENT)_test

UNITY_FOLDER=./Unity
INC_DIRS=-Iproduct
TEST_INC_DIRS=$(INC_DIRS) -I$(UNITY_FOLDER)

SHARED_FILES=product/main.c

ASSIGNMENT_FILES=$(SHARED_FILES)

ASSIGNMENT_TEST_FILES=$(SHARED_FILES) \
	           $(UNITY_FOLDER)/unity.c \
	           test/empty_test.c

SOURCE_FILES=product/linked_list.c

SHARED_LIBRARIES= usr/lib64
SHARED_LIBRARIES_FILES= -lmystack

CC=gcc

SYMBOLS=-g  -O0 -std=c99 -Wall -Wextra -Werror
TEST_SYMBOLS=$(SYMBOLS) -DTEST

.PHONY: clean test klocwork klocwork_after_makefile_change

all: $(ASSIGNMENT)

$(ASSIGNMENT): Makefile $(ASSIGNMENT_FILES)
	$(CC) -I . -c $(SHARED_FILES)
	$(CC) -c $(SOURCE_FILES)
	$(CC) -o exec main.o linked_list.o -lmystack -lm


clean:
	@rm -f $(ASSIGNMENT) exec main.o linked_list.o
	@rm -rf kwinject.out .kwlp .kwps

test: $(ASSIGNMENT_TEST)
	  @valgrind ./$(ASSIGNMENT_TEST)

klocwork:
	@kwcheck run

klocwork_after_makefile_change: clean
	@/opt/klocwork/kwenv.sh
	@kwcheck run
