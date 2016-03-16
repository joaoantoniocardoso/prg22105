#include <stdlib.h>
#include <stdio.h>

int main(){
	int i;
	printf("Digite o numero de elementos: ");
	scanf("%d", &i);
	int v[i];
	v[0]=10;
	v[1]=11;
	v[4]=14;
	int k = 2;

	printf("v[0]: %d,\t v[1]: %d,\t v[4]: %d\n", v[0], v[1], v[4]);
	printf("k: %d\n",k );

	return 0;
}