#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int* revertVector(int *vec, int N);
void printVector(int *vec, int N);
int main(){
	int N,j;
	int *vec;
	
	printf("Entre com o tamanho desejado do vetor de inteiros: ");
	scanf("%d", &N);

	vec = (int*)malloc(sizeof(int)*(N-1));

	printf("Entre com cada inteiro \n");
	for(j=0;j<N;j++){
		printf("inteiro numero %d: ", 1+j);
		scanf("%i", vec);
		vec++;
	}
	vec-=j; //rebobina ponteiro

	printVector(vec,N);
	// int *rvec;
	// rvec = revertVector(vec,N);
	printVector(revertVector(vec,N),N);
	free(vec); //limpa apos terminar sua utilidade
	// free(rvec); //limpa apos terminar sua utilidade -> porque da erro se fizer?
	
	return 0;
}

int* revertVector(int *vec, int N){
	int i;
	int *rvec = (int*)malloc(sizeof(int)*N);
	vec+=N;
	// rvec=vec;
	for (i=0;i<N;i++){
		vec--;
		rvec++;
		*rvec = *vec;
	}
	rvec-=N-1; //nota que por exemplo o quarto elemento equivale ao terceiro
	return rvec;
}

void printVector(int *vec, int N){
	int i;
	for(i=0;i<N;i++){
		printf("%d ", *vec);
		vec++;
	}
	printf("\n");
	vec-=i; //rebobina

}