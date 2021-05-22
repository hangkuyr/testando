CC= gcc

tp1: main.o
	gcc -g -o tp1 main.o tp1.o

main.o: tp1.o
