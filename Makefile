FLAGS = -Wall -ansi -pedantic
DEBUG = -g
TARGETS = listtest listtest-debug studentlisttest student-debug treetest treetest-debug studenttreetest

all: $(TARGETS)

listtest: linkedlist.o listtest.c
	gcc $(FLAGS) $@.c linkedlist.o -o $@

listtest-debug: linkedlistdb.o listtest.c
	gcc $(FLAGS) $(DEBUG) listtest.c linkedlistdb.o -o $@

studentlisttest: linkedlist.o studentlisttest.c
	gcc $(FLAGS) $@.c linkedlist.o -o $@

student-debug: linkedlistdb.o studentlisttest.c
	gcc $(FLAGS) $(DEBUG) studentlisttest.c linkedlistdb.o -o student-debug

linkedlist.o: linkedlist.c
	gcc $(FLAGS) -c linkedlist.c

linkedlistdb.o: linkedlist.c
	gcc $(FLAGS) $(DEBUG) -c linkedlist.c -o $@

treetest-debug: linkedlistdb.o binarytreedb.o treetest.c
	gcc $(FLAGS) $(DEBUG) treetest.c binarytreedb.o linkedlistdb.o -o $@

treetest: linkedlist.o binarytree.o treetest.c
	gcc $(FLAGS) $@.c binarytree.o linkedlist.o -o $@

binarytree.o: binarytree.c
	gcc $(FLAGS) -c binarytree.c

binarytreedb.o: binarytree.c
	gcc $(FLAGS) $(DEBUG) -c binarytree.c -o binarytreedb.o

studenttreetest: binarytree.o linkedlist.o studenttreetest.c
	gcc $(FLAGS) $@.c binarytree.o linkedlist.o -o $@

clean:
	rm -f *.o $(TARGETS)
