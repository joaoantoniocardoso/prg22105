#all:
#	gcc -Wall -c includes/lista-duplamente-encadiada-heterogenea.c -o includes/lista-duplamente-encadiada-heterogenea.o
#	ar rcs libLDEH.a includes/lista-duplamente-encadiada-heterogenea.o
#	gcc -static main.c -L. -lLDEH -o main.out -Wall -lm
#	clear && ./main.out

# project directories
PRJDIR       := $(shell pwd)

OUTDIR       := $(PRJDIR)

LIBDIR       := $(PRJDIR)/lib
OBJDIR       := $(PRJDIR)/obj
CODDIR       := $(PRJDIR)

# C source files

#modules
C_SRC += $(CODDIR)/main.c
C_LIB += $(LIBDIR)/ 
	
# Define programs and commands.
CC      = 	gcc

# compiler flags
CFLAGS  = -lpthread -Ofast -funroll-loops -O3
CFLAGS += -Wall -Wno-write-strings -Wno-return-local-addr
CFLAGS += -g #-std=c++11

#all: pams
# teste: pams main

all: data tree list file menu
	$(CC) $(C_SRC) -o $(OUTDIR)/main -I$(C_LIB) $(CFLAGS) $(OBJDIR)/*.o

%:
	$(CC) $(CFLAGS) -o $(OBJDIR)/$@.o -c $(LIBDIR)/$@.c

clean:	
	rm $(OBJDIR)/* 
	rm $(OUTDIR)/main
	
clean_valgrind:
	rm $(OUTDIR)/vgcore* 
	
clean_linter:
	rm $(LIBDIR)/*.gch

run_val:
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes ./main
run:
	./main