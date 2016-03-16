#include <stdio.h>
#include <stdlib.h>

struct lista{
	int valor;
	struct lista *proximo; 
};

struct lista *inicializar_lista(){
	return NULL;
}

struct lista *criar_lista(int valor_inicial){
	struct lista *mlista = (struct lista*)malloc(sizeof(struct lista));
	(*mlista).proximo = NULL;
	(*mlista).valor = valor_inicial;
	return mlista;
}

struct lista *inserir_lista(struct lista *mlista, int valor_inicial){
	struct lista *primeiro_elemento = criar_lista(valor_inicial);
	(*primeiro_elemento).proximo = mlista;
	return primeiro_elemento;
}

void remover_lista(){

}

void buscar_lista(struct lista *mlista, int valor_procurado){

}

void imprimir_lista(struct lista *mlista){
	int i = 0;
	//fazer copia e trabalhar em cima dela
	//
	printf("A sua lista é: ");
	while((*mlista).proximo !=NULL){
		printf("%d, ", (*mlista).valor);
		mlista++;
	}
	// printf("%d. \n", (*mlista).valor);
	mlista -= i;
}

int main(){
	int a;

	printf("Insira o primeiro inteiro de sua lista: ");
	scanf("%d", &a);
	struct lista *lista1 = criar_lista(a);
	imprimir_lista(lista1);

	printf("Insira um novo elemento em sua lista: ");
	scanf("%d", &a);
	lista1 = inserir_lista(lista1,a);
	imprimir_lista(lista1);



	return 0;
}