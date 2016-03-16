/*
Exercício.

Ler um arquivo  ("num.txt") contendo um conjunto de números inteiros.
Salvar estes valuees em:
A) Um vetor;
b) Uma lista duplamente encadeada;
Fazer um algorítimo de busca binária em um vetor e em uma lista duplamente encadeada.
Verificar os números de passos para execução de cada uma.
Anexar o arquivo e código fonte em um arquivo único <seu_nome.zip>
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FILENAME "num.txt"
#define MAXINT 100

// estruturas da lista
struct list{
	int value;
	struct list *fore;
	struct list *next;
};

struct listHeader{
	int size;
	struct list *start;
	struct list *end;
};

// funcoes de vetor de inteiros
int *readFileToIntVector(const char *filename, unsigned int *n);
void printIntVector(int *v, unsigned int n);
void insertionSortVector(int *v, unsigned int n);
int *binarySearchIntVector(int *vec1, unsigned int n, int value);

// funcoes de lista duplamente encadiada de inteiros
struct listHeader *readFileToIntList(const char *filename);
struct listHeader *createIntList(int value_inicial);
void freeList(struct listHeader *mlista);
struct list *insertIntList(struct listHeader *mlista, int value_inicial);
int removeIntList(struct listHeader *mlista, int value);
void printIntList(struct listHeader *mlista);
struct list *searchIntList(struct listHeader *mlista, int value);
void bubbleSortIntList(struct listHeader *mlista);
void swapPointer (struct list *elemento1, struct list *elemento2);
void insertionSortIntList(struct listHeader* mlista);
int *binarySearchIntList(struct listHeader *mlista, int value);

// funcoes do teste
void runTestVector();
void runTestList();
int randomInt(int n);

// variaveis globais de teste
int value; //o que sera buscado
unsigned long long iterador = 0; //o que conta as iterações para comparação

int main(){
	// elege um numero aleatorio para buscar (variável global)
	value = randomInt(MAXINT);

	printf(".\n\n\n\nEste programa compara implementações de alguns algorítimos recorrentes para vetores e listas duplamente encadiadas a partir da leitura de um arquivo de \ntamanho com uma quantidade indefinida de inteiros únicos e aleatoriamente distirbuídos.\n");

	printf("\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~< VETOR:\n\n");
	runTestVector(); // para um vetor
	printf("\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~< LISTA:\n\n");
	runTestList(); // para uma lista duplamente encadiada

	printf("\n\n\nFim do programa :)\n\n ");

	getchar();
	return 0;
}

void runTestList(){
	clock_t inicio, fim;

	// cria lista a partir do arquivo
	iterador = 0; // zera antes de usar (variável global)
	inicio = clock();
	struct listHeader *lista1 = readFileToIntList(FILENAME);
	fim = clock();
	// printIntList(lista1);
	printf("~> Leitura (lista): %d inteiros lidos em %lf segundos (%.lf clock ticks), executando %llu iterações.\n", (*lista1).size -1, ((double) (fim-inicio))/CLOCKS_PER_SEC,(double) (fim-inicio), iterador);

	// ordena a lista
	iterador = 0;
	inicio = clock();
	insertionSortIntList(lista1);
	fim = clock();
	printf("~> Ordenação 'insertion' (lista): %d inteiros ordenados em %lf segundos (%.lf clock ticks), executando %llu iterações.\n", (*lista1).size -1, ((double) (fim-inicio))/CLOCKS_PER_SEC,(double) (fim-inicio), iterador);

	// executa a busca binaria na lista para o valor aleatorio eleito
	iterador = 0;
	int *ret = (int*)malloc(sizeof(int));
	inicio = clock();
	ret = binarySearchIntList(lista1, value);
	fim = clock();
	printf("~> Busca binária (lista): o inteiro %d foi procurado em uma lista de %d inteiros ", value, (*lista1).size-1);
	if(ret!=NULL) printf("e foi encontrado");
	else printf("e NÃO foi encontrado");
	printf(" em %lf segundos (%.lf clock ticks), executando %llu iterações. \n", ((double) (fim-inicio))/CLOCKS_PER_SEC,(double) (fim-inicio), iterador);

	// desaloca
	freeList(lista1);
}

void runTestVector(){
	unsigned int vec1_size;
	int *vec1;
	clock_t inicio, fim;

	// cria vetor a partir do arquivo
	iterador = 0; // zera antes de usar (variável global)
	inicio = clock();
	vec1 = readFileToIntVector(FILENAME, &vec1_size);
	fim = clock();
	printf("~> Leitura (vetor): %d inteiros lidos em %lf segundos (%.lf clock ticks), executando %llu iterações.\n", vec1_size, ((double) (fim-inicio))/CLOCKS_PER_SEC,(double) (fim-inicio), iterador);

	// ordena o vetor
	iterador = 0;
	inicio = clock();
	insertionSortVector(vec1, vec1_size);
	fim = clock();
	printf("~> Ordenação 'insertion' (vetor): %d inteiros ordenados em %lf segundos (%.lf clock ticks), executando %llu iterações.\n", vec1_size, ((double) (fim-inicio))/CLOCKS_PER_SEC,(double) (fim-inicio), iterador);

	// executa a busca binaria no vetor para o valor aleatorio eleito
	iterador = 0;
	int *ret = (int*)malloc(sizeof(int));
	inicio = clock();
	ret = binarySearchIntVector(vec1, vec1_size, value);
	fim = clock();
	printf("~> Busca binária (vetor): o inteiro %d foi procurado em um vetor de %d inteiros ", value, vec1_size);
	if(ret!=NULL) printf("e foi encontrado");
	else printf("e NÃO foi encontrado");
	printf(" em %lf segundos (%.lf clock ticks), executando %llu iterações. \n", ((double) (fim-inicio))/CLOCKS_PER_SEC,(double) (fim-inicio), iterador);

	// desaloca
	free(vec1);
	vec1=NULL;
}

int *binarySearchIntList(struct listHeader *mlista, int value){
	unsigned int n, a = 0, b = (*mlista).size;
	struct list *mmlista;
	for(n=b/2;(a!=b-1);n=(b+a)/2,iterador++){
		// printf("value=%d ? %d v[%d], a=%d, b=%d \n", value, (*mmlista).value, n+1, a, b); //debug
		mmlista=(*mlista).start;
		for(int i=0;i<n;i++) mmlista = (*mmlista).next;
		if((*mmlista).value==value) return &(*mmlista).value; //encontrado
		else if((*mmlista).value<value) a=n;
		else b=n;
	}
	return NULL; //nao encontrado
}

int *binarySearchIntVector(int *v, unsigned int n, int value){
	unsigned int a=0, b=n;
	for(n=b/2;(a!=b-1);n=(b+a)/2,iterador++){
		//printf("value=%d ? %d v[%d], a=%d, b=%d \n", value, v[n+1], n+1, a, b); //debug
		if(v[n]==value) return &v[n]; //encontrado
		else if(v[n]<value) a=n;
		else b=n;
	}
	return NULL; //nao encontrado
}

int randomInt(int n){
  srand((unsigned)time(NULL));
  return rand()%n+1;
}

void bubbleSortIntList(struct listHeader *mlista){
	struct list *elemento1 = (*mlista).start;
	while(elemento1!=(*mlista).end){
		struct list *elemento2 = (*elemento1).next;
		while(elemento2!=(*mlista).end){
			if((*elemento2).value<(*elemento1).value) swapPointer(elemento1,elemento2);
			elemento2 = (*elemento2).next;
			iterador++;
		}
		elemento1 = (*elemento1).next;
	}
}

void swapPointer (struct list *elemento1, struct list *elemento2){
	int tmp = (*elemento1).value;
	(*elemento1).value = (*elemento2).value;
	(*elemento2).value = tmp;
}

void freeList(struct listHeader *mlista){
	struct list *mmlista = (*mlista).start;
	for (int i=0;i<(*mlista).size-1;i++){
		free(mmlista);
		mmlista = (*mmlista).next;
	}
	free(mlista);
	mlista = NULL;
}

struct listHeader *readFileToIntList(const char *filename){
  FILE *fp = fopen(filename, "r");
  int a,n=0;
	struct listHeader *lista1;

  while(!feof(fp)){
		fscanf(fp, "%d,", &a);
		iterador++;
		if(n==0){
			lista1 = createIntList(a);
			n++;
		}else insertIntList(lista1,a);
	}
  fclose(fp);
	return lista1;
}

int *readFileToIntVector(const char *filename, unsigned int *n){
  FILE *fp = fopen(filename, "r");
	int m;

  for(*n=0;!feof(fp);(*n)++,iterador++) fscanf(fp, "%d,", &m);
  int *u = (int*)malloc(sizeof(*u)*(*n));
  rewind(fp);
  for(*n=0;!feof(fp);(*n)++,iterador++) fscanf(fp, "%d,", &u[*n]);
  fclose(fp);
	(*n)--;
  return u;
}

void insertionSortIntList(struct listHeader* mlista){
	struct list *mmlista = (*mlista).start;

	while(mmlista!=NULL){
		int temp = (*mmlista).value;
		struct list *mmlistb = (*mlista).start;
		while((mmlistb!=mmlista)){
			if((*mmlistb).value > temp){
				(*mmlista).value = (*mmlistb).value;
				(*mmlistb).value = temp;
				temp = (*mmlista).value;
			}
			mmlistb = (*mmlistb).next;
			iterador++;
		}
		mmlista = (*mmlista).next;
	}
}

void insertionSortVector(int *v, unsigned int n){
	int i, j, tmp;
	for(i=0;i<n;i++){
		tmp = v[i];
		for(j=i-1;j>=0 && tmp<v[j];j--,iterador++) v[j+1] = v[j];
		v[j+1] = tmp;
	}
}

void printIntVector(int *v, unsigned int n){
	unsigned int i;
	for(i=0;i<n;i++) printf("%d\t", v[i]);
	printf("\n");
}

void printIntList(struct listHeader *mlista){
	struct list *mmlista = (*mlista).start;
	for(int i=0;i<(*mlista).size-1;i++){
		printf("%d\t", (*mmlista).value);
		mmlista = (*mmlista).next;
	}
	printf("\n");
}

struct listHeader *createIntList(int value_inicial){
	//cria lista
	struct list *mlista = (struct list*)malloc(sizeof(struct list));
	(*mlista).value = value_inicial;
	(*mlista).next = NULL;
	(*mlista).fore = NULL;

	//cria cabecalho
	struct listHeader *mlistHeader = (struct listHeader*)malloc(sizeof(struct listHeader));
	(*mlistHeader).size = 1;
	(*mlistHeader).start = mlista;
	(*mlistHeader).end = mlista;

	return mlistHeader;
}

//insere um elemento no final da lista
struct list *insertIntList(struct listHeader *mlista, int value_inicial){
	struct list *novo_elemento = (struct list*)malloc(sizeof(struct list));
	struct list *ultimo_antigo = (*mlista).end;
	(*ultimo_antigo).next = novo_elemento;
	(*novo_elemento).fore = (*mlista).end;
	(*novo_elemento).value = value_inicial;
	(*mlista).end = novo_elemento;
	(*mlista).size+=1;

	return novo_elemento;
}

struct list *searchIntList(struct listHeader *mlista, int value){
	printf("Buscando...");
	int i;
	struct list *mmlista = (*mlista).start;
	for (i=0;i<(*mlista).size;i++){
		if((*mmlista).value == value){
			printf("\nElemento encontrado.\n");
			return mmlista;
		}else{
		mmlista = (*mmlista).next;
		printf(".");
		}
	}
	printf("\nA lista foi percorrida e o elemento não foi encontrado. Pressione <enter> para continuar.\n");
	getchar();

	return NULL;
}

int removeIntList(struct listHeader *mlista, int value){
	struct list *elemento = searchIntList(mlista, value);
	if (elemento==NULL){
		return -1; //erro
	}else{
		struct list *elemento_fore = (*elemento).fore;
		struct list *elemento_next = (*elemento).next;

		if(elemento == (*mlista).start){
			(*mlista).start = (*elemento).next;
			(*elemento_next).fore = NULL;
		}else if(elemento == (*mlista).end){
			(*mlista).end = (*elemento).fore;
			(*elemento_fore).next = NULL;
		}else{
			(*elemento_fore).next = (*elemento).next;
			(*elemento_next).fore = (*elemento).fore;
		}

		(*mlista).size-=1;
		free(elemento);

		return 0; //ok
	}
}
