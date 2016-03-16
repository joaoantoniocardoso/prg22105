#include <stdio.h>

int main(){
	int a,b[3];
	struct sta{
		char a, b;
		int c;
	} msta;
	struct stb{
		char a;
		int c;
		char b;
	} mstb;
	//sta e stb tem o  mesmo tamanho?
	//en.wikipedia.org/wiki/Data_structure_alignemnt

	printf("tamanho de int a: %d\n", sizeof(a));
	printf("tamanho de int b[3]: %d\n", sizeof(b));
	printf("tamanho de struct sta msta: %d\n", sizeof(msta));
	printf("tamanho de struct stb mstb: %d\n", sizeof(mstb));
	return 0;
}