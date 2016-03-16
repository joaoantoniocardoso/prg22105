#include <stdio.h>
#include <stdlib.h>

//clear && gcc erro1.c && ./a.out

float media(float *notas, int qtd);
void inserirNotas(float *notas, int qtd);
void listarNotas(float *notas, int qtd);

int main(){
	int menu = 0;
	int qtd = 4;
	float *notas = (float*) malloc(sizeof(float) * qtd);
	if(&notas==NULL){
		printf("Erro ao alocar dados na memoria\n");
		return -1;
	}
	do{
		getchar();
		inserirNotas(notas, qtd);
		listarNotas(notas, qtd);

		printf("media: %f\n", media(notas, qtd));

	// TO-DO:
		// printf("Pressione 0 para sair. \n");
		// scanf("%[^\n]i \n", &menu); 
		
	}while(menu!=0);

	free(notas);

	return 0;
}

void inserirNotas(float *notas, int qtd){
	int i;
	printf("Insira %i notas \n", qtd);
	for(i=0;i<qtd;i++){
		scanf("%f", &notas[i]);
		getchar(); //limpar o buffer
	}
}

void listarNotas(float *notas, int qtd){
	int i;
	printf("As notas inseridas foram: \n");
	for(i=0;i<qtd;i++){
		printf("%f \t", notas[i]);
	}
	printf("\n");
}

float media(float *notas, int qtd){
	int i;
	float soma;
	for(i=0;i<qtd;i++){
		soma += notas[i];
	}
	return (float) soma/i;
}
