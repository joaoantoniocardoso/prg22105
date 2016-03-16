all:
	gcc -Wall -c lista-duplamente-encadiada-heterogenea.c -o lista-duplamente-encadiada-heterogenea.o
	ar rcs libLDEH.a lista-duplamente-encadiada-heterogenea.o
	gcc -static testes_LDEH.c -L. -lLDEH -o a.out -Wall -lm
	clear && ./a.out
