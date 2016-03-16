//gcc -v compactador.c -o compactador.o && valgrind --tool=memcheck --leak-check=yes --show-reachable=yes ./compactador.o
#include <stdio.h>
#include <stdlib.h>

////////////////////////////////////////////////////////////////////////////////
// estruturas
////////////////////////////////////////////////////////////////////////////////

struct tree{
	struct tree *esquerda;
  struct tree *direita;
	int freq;
  char c;
};

// estruturas da lista
struct list{
	struct tree *tree;
	struct list *next;
};

struct listHeader{
	int size;
	struct list *start;
	struct list *end;
};

////////////////////////////////////////////////////////////////////////////////
// protótipos
////////////////////////////////////////////////////////////////////////////////

// de lista
struct listHeader *createList(struct tree *mtree);
struct list *insertList(struct listHeader *mlist, struct tree *mtree);
struct listHeader *insertSortedList(struct listHeader *mlH, struct list *mlist);
void insertionSortList(struct listHeader* mlistA);
void printList(struct listHeader *mlist);
struct list *searchListItem(struct listHeader *mlist, struct tree *mtree);
int removeListItem(struct listHeader *mlist, struct list *mmlist);
void freeList(struct listHeader *mlist);

// de árvore
struct tree *createTree(int mfreq, char mc, struct tree *esquerda,
  struct tree *direita);
void printTree(struct tree *mtree);
void freeTree(struct tree *mtree);

// de vetor
void insertionSortVector(int *v, unsigned int n);

// de arquivo
unsigned int *readFileToVector(const char *filename);
#define FILENAME_IN "original.txt"
#define FILENAME_OUT_C "compressed.cbn"
#define FILENAME_OUT_D "decompressed.txt"
#define NCHARS 256

// do algoritimo
// TODO
int compacta(const char *filename);
int descompacta(const char *filename);
void help();
struct listHeader *vectorToListOfTrees(unsigned int *v);
struct tree *makePathTree(struct listHeader *mlH);

////////////////////////////////////////////////////////////////////////////////
// rotinas principais do programa
////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
	//TODO: pegar parametros:
	//			-c [arquivo] para compactar,
	//			-d [arquivo] para descompactar,
	//			imprime help caso contrário.
	// int i = 0;
	// if(argc == 2){
	// 	if(argv[0] == 'c') i = compacta(FILENAME_IN);
	// 	else if(argv[0] == 'd') i = descompacta(FILENAME_IN);
	// }else help();
	// return i;

	return compacta(FILENAME_IN);
}

int compacta(const char *filename)
{
	// ler arquivo e criar vetor de pesos
	unsigned int *vec =	readFileToVector(filename);

	// criar arvore usando o vetor de pesos
	struct listHeader *lista_de_pesos = vectorToListOfTrees(vec);
	// printList(lista_de_pesos); //debug
	struct tree *raiz_da_arvore = makePathTree(lista_de_pesos);
	printTree(raiz_da_arvore); //FIXME

	// TODO: ..and now W.Wallace would like to call for freedom!
	free(vec);
	freeList(lista_de_pesos);
	// freeTree(raiz_da_arvore); //FIXME

	return 0;
}

int descompacta(const char *filename)
{
	return 0;
}

void help(){
	printf("Este programa utiliza o algorítimo de Huffman para compactar e \n descompactar arquivos.\n");
	printf("Modo de uso:\n");
	printf("\t -c\t [arquivo]\t compacta \n");
	printf("\t -d\t [arquivo]\t descompacta \n");
}

////////////////////////////////////////////////////////////////////////////////
// funções de árvore
////////////////////////////////////////////////////////////////////////////////

struct tree *createTree(int mfreq, char mc, struct tree *esquerda,
  struct tree *direita)
{
	struct tree *mtree = (struct tree*)malloc(sizeof(struct tree));
	(*mtree).freq = mfreq;
	(*mtree).c = mc;
	(*mtree).direita = direita;
	(*mtree).esquerda = esquerda;

	return mtree;
}

void printTree(struct tree *mtree)
{
	if (mtree!=NULL) printf("<%d[%c]",(*mtree).freq, (*mtree).c);
	else printf("<>");
	if ((*mtree).esquerda!=NULL) printTree((*mtree).esquerda);
	else printf("<>");
	if ((*mtree).direita!=NULL) printTree((*mtree).direita);
	else printf("<>");
	printf(">");
}

void freeTree(struct tree *mtree)
{
	if((*mtree).esquerda != NULL) freeTree((*mtree).esquerda);
	if((*mtree).direita != NULL)  freeTree((*mtree).direita);
	free(mtree);
}

////////////////////////////////////////////////////////////////////////////////
// funções de lista
////////////////////////////////////////////////////////////////////////////////

struct listHeader *createList(struct tree *mtree)
{
	//cria lista
	struct list *mlist = (struct list*)malloc(sizeof(struct list));
	(*mlist).tree = mtree;
	(*mlist).next = NULL;

	//cria cabecalho
	struct listHeader *mlistHeader = (struct listHeader*)malloc(sizeof(struct listHeader));
	(*mlistHeader).size = 1;
	(*mlistHeader).start = mlist;
	(*mlistHeader).end = mlist;

	return mlistHeader;
}

// insere um elemento no final da lista
struct list *insertList(struct listHeader *mlist, struct tree *mtree)
{
	struct list *novo_elemento = (struct list*)malloc(sizeof(struct list));
	struct list *ultimo_antigo = (*mlist).end;
	(*ultimo_antigo).next = novo_elemento;
	(*novo_elemento).tree = mtree;
	(*mlist).end = novo_elemento;
	(*mlist).size += 1;

	return novo_elemento;
}

// insere elemento em ordem crescente
struct listHeader *insertSortedList(struct listHeader *mlH, struct list *mlist)
{
	// caso inicial, quando a lista foi inicializada com nulo
	if( (*(*mlH).start).tree == NULL ){
		(*mlH).start = mlist;
	}else{
		struct list *p = (*mlH).start; //ponteiro que percorre a lista
		struct list *q = NULL; //ponteiro sempre anterior ao p

		// encontra a posição
		while( ((*p).next != NULL) && ((*(*mlist).tree).freq > (*(*p).tree).freq) ){
			q = p; // guarda anterior
			p = (*p).next;
		}

		// insere o elemento
		if(q == NULL){ // no início
			(*mlist).next = (*mlH).start;
			(*mlH).start = mlist;
		}else if( (*q).next == NULL ){ // no fim
			(*mlH).end = q = mlist;
		}else{ // no meio
			(*mlist).next = p;
			(*q).next = mlist;
		}
		(*mlH).size++;
	}
	return mlH;
}

void insertionSortList(struct listHeader* mlistA)
{
	struct list *mmlistA = (*mlistA).start;
	while(mmlistA!=NULL){

		int temp = (*(*mmlistA).tree).freq;
		struct list *mmlistB = (*mlistA).start;
		while((mmlistB!=mmlistA)){
			if((*(*mmlistB).tree).freq > temp){
				(*(*mmlistA).tree).freq = (*(*mmlistB).tree).freq;
				(*(*mmlistB).tree).freq = temp;
				temp = (*(*mmlistA).tree).freq;
			}
			mmlistB = (*mmlistB).next;
		}
		mmlistA = (*mmlistA).next;
	}
}

void printList(struct listHeader *mlist)
{
	struct list *mmlist = (*mlist).start;
	for(int i=0;i<(*mlist).size-1;i++){
		printf("::%d, %c\n", (*(*mmlist).tree).freq, (*(*mmlist).tree).c);
		mmlist = (*mmlist).next;
	}
	printf("\n");
}

struct list *searchListItem(struct listHeader *mlist, struct tree *mtree)
{
	int i;
	struct list *mmlist = (*mlist).start;
	for (i=0;i<(*mlist).size;i++){
		if((*mmlist).tree == mtree){
			return mmlist; // encontrado
		}else{
		mmlist = (*mmlist).next;
		}
	}

	return NULL; //nao encontrado
}

//  		  FIXME
//  		    ||
//  		    \/
int removeListItem(struct listHeader *mlist, struct list *mmlist)
{
	if (mmlist==NULL){
		return -1;
	}else{
    struct list *p = (*mlist).start; //ponteiro para o anterior

		// remove
    if(mmlist == (*mlist).start){ 							// do inicio
      (*mlist).start = (*mmlist).next;
    }else{
			// busca o anterior ao que vai remover
			for(int i=0; (i<(*mlist).size-1) && ((*p).next!=mmlist); i++)
				p = (*p).next;
			if(mmlist == (*mlist).end){ 							// do fim
				(*mlist).end = p;
				(*p).next = NULL;
			}else{ 																		// do meio
				(*p).next = (*mmlist).next;
			}
		}

		(*mlist).size--;
		free(mmlist);

		return 0;
	}
}

void freeList(struct listHeader *mlist)
{
	struct list *mmlist = (*mlist).start;
	for (int i=0;i<(*mlist).size-1;i++){
		free(mmlist);
		mmlist = (*mmlist).next;
	}
	free(mlist);
	mlist = NULL;
}

////////////////////////////////////////////////////////////////////////////////
// funções de vetor
////////////////////////////////////////////////////////////////////////////////

void insertionSortVector(int *v, unsigned int n)
{
	int i, j, tmp;
	for(i=0;i<n;i++){
		tmp = v[i];
		for(j=i-1;j>=0 && tmp<v[j];j--) v[j+1] = v[j];
		v[j+1] = tmp;
	}
}

////////////////////////////////////////////////////////////////////////////////
// funções de arquivo
////////////////////////////////////////////////////////////////////////////////

// le do arquivo e cria vetor de pesos
unsigned int *readFileToVector(const char *filename)
{
	FILE *fp = fopen(filename, "r");
	unsigned int *u = (unsigned int*)calloc(NCHARS, sizeof(unsigned int*));
	char m;

	while(!feof(fp)){
		fscanf(fp, "%c,", &m);
		u[(int)m]++;
		// printf("%d:\t%d \n", m, u[(int)m] ); //debug
	}

	fclose(fp);
	return u;
}

////////////////////////////////////////////////////////////////////////////////
// funções do algoritimo de huffman
////////////////////////////////////////////////////////////////////////////////

// cria lista de arvores de um dado vetor de pesos
struct listHeader *vectorToListOfTrees(unsigned int *v)
{
	struct listHeader *mlH = createList(NULL); //cria lista
	for(int i = 0; i < 150; i++){
		if(v[i] != 0){
			// printf(".");
			struct list *mlist = (struct list*)malloc(sizeof(struct list));
			(*mlist).tree = createTree(v[i], i, NULL, NULL);
			insertSortedList(mlH, mlist);
		}
	}

	return mlH;
}

//  		  FIXME
//  		    ||
//  		    \/
struct tree *makePathTree(struct listHeader *mlH)
{
	struct list *mlist1 = (*mlH).start, *mlist2;

	while( (*mlH).start != (*mlH).end ){

		mlist1 = (*mlH).start;
		mlist2 = (*mlist1).next;

		// cria um novo nó contendo como filhos os dois primeiros da lista ordenada
		// 		e insere ordenadamente como um novo item da lista
		(*mlist1).tree = createTree(
			(*(*mlist1).tree).freq + (*(*mlist2).tree).freq,
			'\0',
			(*mlist1).tree, (*mlist2).tree
		);

		// printf("\t %d: %d\n", (*(*mlist3).tree).c, (*(*mlist3).tree).freq ); // debug

		insertSortedList(mlH, mlist1);

		// remove
		(*mlH).start = (*mlist2).next;
		(*mlH).size--;
		// free(mlist2);

	}

	return (*mlist1).tree;
}





















////////////////////////////////////////////////////////////////////////////////
