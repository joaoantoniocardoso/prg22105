#include "stdio.h"
#include "stdlib.h"

struct lista{
	int valor;
	struct lista *anterior;
	struct lista *proximo;
};

struct cabecalho_lista{
	int size;
	struct lista *start;
	struct lista *end;
};

struct cabecalho_lista *criar_lista(int valor_inicial){
	//cria lista
	struct lista *mlista = (struct lista*)malloc(sizeof(struct lista));
	(*mlista).valor = valor_inicial;
	(*mlista).proximo = NULL;
	(*mlista).anterior = NULL;

	//cria cabecalho
	struct cabecalho_lista *mcabecalho_lista = (struct cabecalho_lista*)malloc(sizeof(struct cabecalho_lista));
	(*mcabecalho_lista).size = 1;
	(*mcabecalho_lista).start = mlista;
	(*mcabecalho_lista).end = mlista;

	return mcabecalho_lista;
}

//insere um elemento no final da lista
struct lista *inserir_elemento_final(struct cabecalho_lista *mlista, int valor_inicial){
	struct lista *novo_elemento = (struct lista*)malloc(sizeof(struct lista));
	struct lista *ultimo_antigo = (*mlista).end;
	(*ultimo_antigo).proximo = novo_elemento;
	(*novo_elemento).anterior = (*mlista).end;
	(*novo_elemento).valor = valor_inicial;
	(*mlista).end = novo_elemento;
	(*mlista).size+=1;

	return novo_elemento;
}

struct lista *busca_elemento(struct cabecalho_lista *mlista, int valor){
	printf("Buscando...");
	int i;
	struct lista *mmlista = (*mlista).start;
	for (i=0;i<(*mlista).size;i++){
		if((*mmlista).valor == valor){
			printf("\nElemento encontrado.\n");
			return mmlista;
		}else{
		mmlista = (*mmlista).proximo;
		printf(".");
		}
	}
	printf("\nA lista foi percorrida e o elemento não foi encontrado. Pressione <enter> para continuar.\n");
	getchar();

	return NULL;
}

int remover_elemento(struct cabecalho_lista *mlista, int valor){
	struct lista *elemento = busca_elemento(mlista, valor);
	if (elemento==NULL){

		return -1; //erro
	}else{
		struct lista *elemento_anterior = (*elemento).anterior;
		struct lista *elemento_proximo = (*elemento).proximo;
		
		if(elemento == (*mlista).start){
			(*mlista).start = (*elemento).proximo;
			(*elemento_proximo).anterior = NULL;
		}else if(elemento == (*mlista).end){
			(*mlista).end = (*elemento).anterior;
			(*elemento_anterior).proximo = NULL;
		}else{
			(*elemento_anterior).proximo = (*elemento).proximo;
			(*elemento_proximo).anterior = (*elemento).anterior;
		}

		(*mlista).size-=1;
		free(elemento);

		return 0; //ok
	}
}

void imprimir_lista(struct cabecalho_lista *mlista){
	printf("A sua lista é: ");
	struct lista *mmlista = (*mlista).start;
	int i;
	for (i = 0; i < (*mlista).size ; i++){
		printf("%d, ", (*mmlista).valor);
		mmlista = (*mmlista).proximo;
	}
}

int main(){
	int a;

	printf("Insira o primeiro inteiro de sua lista: ");
	scanf("%d", &a);
	struct cabecalho_lista *lista1 = criar_lista(a);
	imprimir_lista(lista1);
	int i;
	for(i = 0; i<10; i++){
		printf("\nInsira um novo elemento em sua lista: ");
		scanf("%d", &a);
		inserir_elemento_final(lista1,a);
		imprimir_lista(lista1);
	}
	getchar();
	printf("\nInsira um elemento a ser removido da lista: ");
	scanf("%d", &a);
	if (!remover_elemento(lista1,a)){
		printf("\nO valor foi removido\n");
		imprimir_lista(lista1);
	}
	getchar;

	return 0;
}