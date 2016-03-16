#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "lista-duplamente-encadiada-heterogenea.h"

struct dados{
	int i;
	char c;
};

static void *imprimir_item(void *dado, int n, va_list vargs);
static void *busca_item(void *dado, int n, va_list vargs);

int main(){
	int a;
	char c;
	struct dados *dado_temp, *dado_temp2;

	//testando a criação da lista
	printf("Insira o primeiro item de sua lista no formato <inteiro,char> ");
	dado_temp = (struct dados*)malloc(sizeof(struct dados));
	scanf("%d,%c", &a, &c);
	getchar(); //limpar o buffer
	(*dado_temp).i = a;
	(*dado_temp).c = c;
	struct lista *lista1 = criar_lista((void*)dado_temp);
	printf("A sua lista é: ");
	percorre_lista(lista1, &imprimir_item, 0);
	
	//testando inserção de dados na lista
	int i;
	for(i = 0; i<2; i++){
		printf("\nInsira um novo elemento em sua lista no formato <inteiro,char>: ");
		dado_temp = (struct dados*)malloc(sizeof(struct dados));
		scanf("%d,%c", &a, &c);
		getchar();
		(*dado_temp).i = a;
		(*dado_temp).c = c;
		inserir_elemento_final(lista1, (void*)dado_temp);
		printf("A sua lista é: ");
		percorre_lista(lista1, &imprimir_item, 0);
	}	

	//testando a remoção de dados na lista
	printf("\nInsira um elemento a ser removido da lista no formato <inteiro,char>: ");
	scanf("%d,%c", &a, &c);

	// faz uma busca pelo dado
	printf("Buscando...");
	dado_temp2 = (struct dados*)percorre_lista(lista1, &busca_item, 2, a, c);
	// verifica se foi encontrado
	if(dado_temp2!=NULL){
		printf("\nElemento encontrado: ");
		imprimir_item(dado_temp2, 0, NULL);
	}else printf("\n O elemento buscado não foi encontrado. \n");

	// tenta remover o elemento e verifica
	if(dado_temp2 != NULL){
		dado_temp2 = remover_elemento(lista1, (void*)dado_temp2);
		if (dado_temp2!=NULL){
			printf("\nO elemento foi removido. \n");
		}else printf("O elemento não foi removido. \n");
	}
	//Obs: se quiser remover elementos repetidos pode usar um laço até o remover_elemento retornar NULL.

	// lista novamente
	printf("A sua lista é: ");
	percorre_lista(lista1, &imprimir_item, 0);

	getchar();

	return 0;
}

static void *imprimir_item(void *dado, int n, va_list vargs){
	struct dados *mdado = dado;
	printf("%d,", (*mdado).i);
	printf("%c", (*mdado).c);
	printf("\t");
	return NULL;
}

static void *busca_item(void *dado, int n, va_list vargs){
	int a=0;

	struct dados *mdado = (struct dados*) dado;
	
	//recebe os parametros em ordem
	int icomp = (int) va_arg(vargs, int);
	char ccomp = (char) va_arg(vargs, int);

	//começa a comparação
	if((*mdado).i == icomp) a++;
	if((*mdado).c == ccomp) a++;

	//retorna
	// return dado;
	if(a>1) return mdado;
	else return NULL;
}