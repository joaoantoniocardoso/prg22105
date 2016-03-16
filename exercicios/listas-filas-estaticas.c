//1) Escreva um algoritmo do tipo função iguais (L1, L2) que retorne um valor lógico: Verdadeiro, se L1 = L2 e Falso, se L1 <> L2. L1 e L2 são listas lineares. 

// 2) Escreva um algoritmo copia (L1, L2) para montar uma cópia L2 da lista L1. 

#include <stdio.h>
#include <stdlib.h>

const int TAMANHO = 10;
typedef int TIPODADO;

char iguais(TIPODADO *L1, TIPODADO *L2){
	int i;
	for (i=0;i<TAMANHO;i++) if(L1[i]!= L2[i]) return 0; //falso
	return 1; //verdadeiro
}

char copia(TIPODADO *L1, TIPODADO *L2){
	int i;
	for (i=0;i<TAMANHO;i++) L1[i] = L2[i];
	return 0;
}

int main(){
	//cria lista estatica
	TIPODADO lista1[TAMANHO];
	TIPODADO lista2[TAMANHO];
	int i;

	//zera as listas
	for (i=0; i<TAMANHO; i++)
		lista1[i]=lista2[i]=0; 
	
	//modifica uma das listas
	lista1[2]=1;

	//testa se sao iguais passando ponteiros
	if (iguais(lista1,lista2)) printf("IGUAIS\n");
	else printf("DIFERENTES\n");

	copia(lista1,lista2);

	//testa se sao iguais passando ponteiros
	if (iguais(lista1,lista2)) printf("IGUAIS\n");
	else printf("DIFERENTES\n");


	return 0;
}