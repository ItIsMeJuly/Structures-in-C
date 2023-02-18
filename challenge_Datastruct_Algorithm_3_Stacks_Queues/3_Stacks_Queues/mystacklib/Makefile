ASSIGNMENT=mystack
ASSIGNMENT_TEST=$(ASSIGNMENT)_test

UNITY_FOLDER=./Unity
INC_DIRS=-Isrc
TEST_INC_DIRS=$(INC_DIRS) -I$(UNITY_FOLDER)

SHARED_FILES=src/mystack.c

ASSIGNMENT_TEST_FILES=$(SHARED_FILES) \
	           $(UNITY_FOLDER)/unity.c \
	           test/mystack_test.c

HEADER_FILES=src/*.h

CC=gcc

TARGET  = libmystack.so
SOURCES = src/mystack.c
OBJECTS = $(SOURCES:.c=.o)
CFLAGS       = -fPIC -c #-pedantic -Wall -Wextra -ggdb3
LDFLAGS      = -shared -o


SYMBOLS=-g  -O0 -std=c99 -Wall -Wextra -Werror
TEST_SYMBOLS=$(SYMBOLS) -DTEST

.PHONY: clean test klocwork klocwork_after_makefile_change

all: mystack.o $(TARGET) 

$(ASSIGNMENT_TEST): Makefile $(ASSIGNMENT_TEST_FILES)  $(HEADER_FILES)
	$(CC) $(TEST_INC_DIRS) $(TEST_SYMBOLS) $(ASSIGNMENT_TEST_FILES) -o $(ASSIGNMENT_TEST)

mystack.o: $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES)

$(TARGET): $(mystack.o)
	$(CC) $(LDFLAGS) $(TARGET) mystack.o	



clean:
	@rm -f $(ASSIGNMENT) $(ASSIGNMENT_TEST) mystack.o libmystack.so
	@rm -rf kwinject.out .kwlp .kwps

test: $(ASSIGNMENT_TEST)
	  @valgrind ./$(ASSIGNMENT_TEST)

klocwork:
	@kwcheck run

klocwork_after_makefile_change: clean
	@/opt/klocwork/kwenv.sh
	@kwcheck run
