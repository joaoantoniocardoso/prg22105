// 	OBS: 
//	TRABALHANDO COM LISTAS DINAMICAS (duplamente encadiada) AO INVES DO PROPOSTO PELOS EXERCICIOS
#include <stdio.h>
#include <stdlib.h>

typedef int TIPODADO;

struct itemlista{
	TIPODADO dado;
	struct itemlista *proximo;
	struct itemlista *anterior;
};

struct lista{
	int size;
	struct itemlista *start;
	struct itemlista *end;
};

//cria a lista já com um item com valor inicial
struct lista *criar_lista(TIPODADO valor_inicial){
	//cria lista
	struct itemlista *mlista = (struct itemlista*)malloc(sizeof(struct itemlista));
	(*mlista).dado = valor_inicial;
	(*mlista).proximo = NULL;
	(*mlista).anterior = NULL;

	//cria cabecalho
	struct lista *mcabecalho_lista = (struct lista*)malloc(sizeof(struct lista));
	(*mcabecalho_lista).size = 1;
	(*mcabecalho_lista).start = mlista;
	(*mcabecalho_lista).end = mlista;

	return mcabecalho_lista;
}

//insere um item no final da lista
struct itemlista *insereFinal(struct lista *mlista, TIPODADO valor_inicial){
	struct itemlista *novoitem = (struct itemlista*)malloc(sizeof(struct itemlista));
	struct itemlista *ultimo_antigo = (*mlista).end;
	(*ultimo_antigo).proximo = novoitem;
	(*novoitem).anterior = (*mlista).end;
	(*novoitem).dado = valor_inicial;
	(*mlista).end = novoitem;
	(*mlista).size+=1;

	return novoitem;
}

//insere um item no inicio da lista
struct itemlista *insereInicio(struct lista *mlista, TIPODADO valor_inicial){
	struct itemlista *novo_elemento = (struct itemlista*)malloc(sizeof(struct itemlista));

	(*novo_elemento).proximo = (*mlista).start;
	(*novo_elemento).dado = valor_inicial;

	(*mlista).start = novo_elemento;
	(*mlista).size+=1;

	return novo_elemento;
}

//1) Escreva um algoritmo do tipo função iguais (L1, L2) que retorne um valor lógico: Verdadeiro, se L1 = L2 e Falso, se L1 <> L2. L1 e L2 são listas lineares. 
char iguais(struct lista *L1, struct lista *L2){
	if ((*L1).size!=(*L2).size) return -1; //erro: tamanhos diferentes
	int i;
	struct itemlista *item1 = (*L1).start, *item2 = (*L2).start;
	for (i=0;i<(*L1).size;i++) {
		if((*item1).dado != (*item2).dado) return 0; //falso
		item1 = (*item1).proximo;
		item2 = (*item2).proximo;
	}
	return 1; //verdadeiro
}

// 2) Escreva um algoritmo copia (L1, L2) para montar uma cópia L2 da lista L1. 
char copia(struct lista *L1, struct lista *L2){
	if ((*L1).size!=(*L2).size) return -1; //erro: tamanhos diferentes
	int i;
	struct itemlista *item1 = (*L1).start, *item2 = (*L2).start;
	for (i=0;i<(*L1).size;i++) {
		(*item1).dado = (*item2).dado;
	}
	return 0; //ok
}

// 3) Escreva um algoritmo diferença (L, L1, L2) para construir a lista linear L igual à diferença L1-L2. 
char diferenca(struct lista *L, struct lista *L1, struct lista *L2){
	if ((*L1).size!=(*L2).size!=(*L).size) return -1; //erro: tamanhos diferentes
	int i;
	struct itemlista *item1 = (*L1).start, *item2 = (*L2).start, *itemret = (*L).start;;
	for (i=0;i<(*L1).size;i++) {
		(*itemret).dado = (*item1).dado - (*item2).dado;
	}
	return 0; //ok
}

// 4) Escreva um algoritmo comuns (L1, L2) do tipo função, o qual deve retornar um valor inteiro igual ao número de valores comuns em duas listas ordenadas L1 e L2.
char comuns(struct lista *L1, struct lista *L2){
	if ((*L1).size!=(*L2).size) return -1; //erro: tamanhos diferentes
	int i, j;
	struct itemlista *item1 = (*L1).start, *item2 = (*L2).start;
	for (i=0, j=0;i<(*L1).size;i++) if((*item1).dado == (*item2).dado) j++;
	return j; //ok
}

// 5) Escreva um algoritmo insereOrd (L,i) para inserir um nó com a informação i na lista ordenada L, preservando a ordem crescente dos valores na lista. 
char insereOrd(struct lista *L, int i){
	int j;
	struct itemlista *mitemlista = (*L).start;
	struct itemlista *novoitem = (struct itemlista*)malloc(sizeof(struct itemlista*));


	//encontra a posição
	for (j=0, j=0;j<(*L).size;j++) {
		if((*mitemlista).dado > i) break;
		mitemlista = (*mitemlista).proximo;
	}

	//reaponta
	(*novoitem).proximo = (*mitemlista).proximo;
	(*novoitem).anterior = (*mitemlista).anterior;
	(*(*mitemlista).proximo).anterior = novoitem;
	(*(*mitemlista).anterior).proximo = novoitem;

	return 0; //ok
}

/*

6) Considere um conjunto de informações relativas a alunos, constituído de nome, número
de matrícula e data de nascimento. Organize estas informações em uma lista ordenada pelo
número da matrícula do aluno. Escreva subprogramas que efetuem as seguintes ações:
	a. imprimir os nomes e números de matrícula dos alunos que nasceram após uma
determinada data (passada como parâmetro);
	b. procurar as informações relativas a um determinado aluno, cujo número de
matrícula é passado como parâmetro;
	c. incluir um novo aluno na lista, respeitando a ordenação. 

*/

int main(){
	// //cria lista dinamica
	// TIPODADO lista1[TAMANHO];
	// TIPODADO lista2[TAMANHO];
	// int i;

	// //zera as listas
	// for (i=0; i<TAMANHO; i++)
	// 	lista1[i]=lista2[i]=0; 
	
	// //modifica uma das listas
	// lista1[2]=1;

	// //testa se sao iguais passando ponteiros
	// if (iguais(lista1,lista2)) printf("IGUAIS\n");
	// else printf("DIFERENTES\n");

	// copia(lista1,lista2);

	// //testa se sao iguais passando ponteiros
	// if (iguais(lista1,lista2)) printf("IGUAIS\n");
	// else printf("DIFERENTES\n");


	return 0;
}