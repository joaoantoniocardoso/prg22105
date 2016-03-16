#include <stdio.h>
#include <stdlib.h>

struct itemfila{
	int valor;
	struct itemfila *proximo;
};

struct fila{
	struct itemfila *start;
	int size; 
};

struct fila *criar_fila(int a){
	//cria fila
	struct itemfila *mitemfila = (struct itemfila*)malloc(sizeof(struct itemfila));
	(*mitemfila).valor = a;
	(*mitemfila).proximo = NULL;

	//cria cabecalho
	struct fila *mfila = (struct fila*)malloc(sizeof(struct fila));
	(*mfila).size = 1;
	(*mfila).start = mitemfila;

	return mfila;
}

//insere um elemento no inicio da fila
struct itemfila *inserir_elemento(struct fila *mfila, int valor_inicial){
	struct itemfila *novo_elemento = (struct itemfila*)malloc(sizeof(struct itemfila));

	(*novo_elemento).proximo = (*mfila).start;
	(*novo_elemento).valor = valor_inicial;

	(*mfila).start = novo_elemento;
	(*mfila).size+=1;

	return novo_elemento;
}

struct itemfila *busca_elemento(struct fila *mfila, int valor){
	printf("Buscando...");
	int i;
	struct itemfila *mitemfila = (*mfila).start;
	for (i=0;i<(*mfila).size;i++){
		if((*mitemfila).valor == valor){
			printf("\nElemento encontrado.\n");
			return mitemfila;
		}else{
		mitemfila = (*mitemfila).proximo;
		printf(".");
		}
	}
	printf("\nA fila foi percorrida e o elemento não foi encontrado. Pressione <enter> para continuar.\n");
	getchar();

	return NULL;
}

int remover_elemento(struct fila *mfila, struct itemfila *ret_itemremovido){
	struct itemfila *mitemfila = (*mfila).start;
	if ((*mfila).size==0) return -2; //fila vazia
	if (mitemfila==NULL) return -1; //erro
	else{
		if((*mitemfila).proximo!=NULL) (*mfila).start = (*mitemfila).proximo;
		(*mfila).size-=1;
		ret_itemremovido = mitemfila;
		free(mitemfila);
		return 0; //ok
	}
}

void imprimir_fila(struct fila *mfila){
	printf("A sua fila é: ");
	struct itemfila *mitemfila = (*mfila).start;
	int i;
	for (i = 0; i < (*mfila).size ; i++){
		printf("%d, ", (*mitemfila).valor);
		mitemfila = (*mitemfila).proximo;
	}
}

int main(){
	int a;
	printf("\nInsira o primeiro elemento em sua fila: ");
	scanf("%d", &a);
	struct fila *fila1 = criar_fila(a);
	imprimir_fila(fila1);
	int i;
	for(i = 0; i<0; i++){
		printf("\nInsira um elemento em sua fila: ");
		scanf("%d", &a);
		inserir_elemento(fila1,a);
		imprimir_fila(fila1);
	}
	getchar();
	printf("\nUm elemento sera removido da fila: ");
	struct itemfila *item_temp1 = (struct itemfila*)malloc(sizeof(struct itemfila));
	if (!remover_elemento(fila1, item_temp1)){
		printf("\nUm item foi removido\n");
		free(item_temp1);
	}else printf("\nNenhum item foi removido\n");
	imprimir_fila(fila1);
	getchar;

	return 0;
}
