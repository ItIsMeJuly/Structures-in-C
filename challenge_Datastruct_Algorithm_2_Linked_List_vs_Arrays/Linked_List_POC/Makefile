ASSIGNMENT=linkedlist

INC_DIRS=-Iproduct
SHARED_FILES=product/linked_list.c

ASSIGNMENT_FILES=$(SHARED_FILES) \
	      product/main.c

HEADER_FILES=product/*.h

CC=gcc

SYMBOLS=-g -O0 -std=c99 -Wall -Wextra -Werror

.PHONY: clean klocwork klocwork_after_makefile_change

all: $(ASSIGNMENT)

$(ASSIGNMENT): Makefile $(ASSIGNMENT_FILES)  $(HEADER_FILES)
	$(CC) $(INC_DIRS) $(SYMBOLS) $(ASSIGNMENT_FILES) -o $(ASSIGNMENT)

clean:
	@rm -f $(ASSIGNMENT)
	@rm -rf kwinject.out .kwlp .kwps

klocwork:
	@kwcheck run

klocwork_after_makefile_change: clean
	@/opt/klocwork/kwenv.sh
	@kwcheck run

