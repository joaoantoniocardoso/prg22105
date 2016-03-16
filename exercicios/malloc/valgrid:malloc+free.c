// valgrind --tool=memcheck --leak-check=yes --show-reachable=yes ./a.out 

#include <stdio.h>
#include <stdlib.h>

int main(){
	printf("\n\n\t\t::batata::\n\n");
	int a = 2;
	int *b = (int*)malloc(sizeof(int));
	*b = a+1;
	printf("\t%d,\t%d\n\n", a, *b);
	free(b);
	return 0;
}