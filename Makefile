FLAGS=-Wextra -Wall -Werror -pedantic -std=c99

all: start

start: basfunc.o exptree.o token.o main.o
	gcc $(FLAGS) -o lab24 basfunc.o exptree.o token.o main.o -L. lib/libqueue.a lib/libstack.a

main.o: main.c
	gcc -c $(FLAGS) main.c

exptree.o: exptree.h exptree.c
	gcc -c $(FLAGS) exptree.h exptree.c

stack.o: stack.h stack.c
	gcc -c $(FLAGS) stack.h stack.c

basfunc.o: basfunc.h basfunc.c
	gcc -c $(FLAGS) basfunc.h basfunc.c

token.o: token.h token.c
	gcc -c $(FLAGS) token.h token.c


clear:
	-rm -f *.o *.gch lab24

lib: exptree.o
	ar rc lib/libexptree.a exptree.o
	ranlib lib/libexptree.a
libstack: stack.o
	ar rc lib/libstack.a stack.o
	ranlib lib/libstack.a