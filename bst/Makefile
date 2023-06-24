bst: tree.o bst.o
	gcc -o bst bst.o tree.o -Wall -Wextra -g

tree.o: tree.c tree.h
	gcc -c -o tree.o tree.c -Wall -Wextra -g

bst.o: bst.c tree.h
	gcc -c -o bst.o bst.c -Wall -Wextra -g