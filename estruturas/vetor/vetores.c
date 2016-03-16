#include <stdio.h>
#include <time.h>

//clear && gcc erro1.c && ./a.out

#define QTD 5

	float notas[QTD];

float media(float *notas);
void inserirNotas(float *notas);
void listarNotas(float *notas);

int main(){
	int menu = 1;
	do{
		getchar();
		inserirNotas(notas);
		listarNotas(notas);

		float resultado = media(notas);

		printf("media: %f\n", resultado);

		printf("Pressione 0 para sair. \n");
		// TO-DO:
		// scanf("%[^\n]i \n", &menu); 
		
	}while(menu!=0);

	return 0;

}

void inserirNotas(float *notas){
	int i;
	printf("Insira %i notas \n", QTD);
	for(i=0;i<QTD;i++){
		scanf("%f", &notas[i]);
		getchar(); //limpar o buffer
	}
	
}

void listarNotas(float *notas){
	int i;
	printf("As notas inseridas foram: \n");
	for(i=0;i<QTD;i++){
		printf("%f \t", notas[i]);
	}
	printf("\n");
}

float media(float *notas){
	int i;
	int soma;
	for(i=0;i<QTD;i++){
		soma += notas[i];
	}
	return (float)soma/i;
}
