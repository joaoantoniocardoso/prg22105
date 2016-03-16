#include <stdio.h>
#include <stdlib.h>
#include <string.h>

////////////////////////////////////////////////////////////////////////////////
// estruturas
////////////////////////////////////////////////////////////////////////////////

struct tree{
	struct tree *l;
  struct tree *r;
	unsigned int f;
  unsigned char c;
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

// branch prediction via compilador
#define likely(x)			__builtin_expect((x),1)
#define unlikely(x)		__builtin_expect((x),0)

// de lista
struct listHeader *createList(struct tree *mtree);
struct listHeader *insertSortedList(struct listHeader *mlH, struct tree *mtree);
void insertionSortList(struct listHeader* mlistA);
void printList(struct listHeader *mlist);
void freeList(struct listHeader *mlist);

// de árvore
struct tree *createTree(int mf, char mc, struct tree *l,
  struct tree *r);
void printTree(struct tree *mtree);
void freeTree(struct tree *mtree);

// de vetor
void insertionSortVector(int *v, unsigned int n);
unsigned int *createfVector(unsigned char *buffer);
#define BIT(I,N) I&(1<<N) // máscara para o enésemo bit de I
int for1BLim(int x);
void printBinary(int x);
void stringToBinary(char* x, char* texto);

// de arquivo
unsigned char *readFileToBuffer(const char *filename);
void writeToFile(char *filename, unsigned char *header, unsigned char *body);
#define FILENAME_IN "original.txt"
#define FILENAME_OUT_C "compressed.hcf" //Huffman compressed file
#define FILENAME_OUT_D "decompressed.txt"
#define NCHARS 256

// do algoritimo
// TODO
#define ENDOFFILE 0 // '\0'
int compacta(const char *filename);
int descompacta(const char *filename);
void help();
struct listHeader *vectorToListOfTrees(unsigned int *v);
struct tree *makePathTree(struct listHeader *mlH);
void createTable(struct tree *mtree,
	unsigned char pathTable[][9],
	unsigned char *v,
	unsigned char i
);
unsigned char *writeHeader(struct tree *mtree);
void createHeader(struct tree *mtree, unsigned char *header, int *i);
unsigned char *writeBody(unsigned char pathTable[][9],
	unsigned char *fileBuffer);

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

// função que compacta
int compacta(const char *filename)
{
	// le arquivo e cria vetor de pesos
	unsigned char *fileBuffer = readFileToBuffer(filename);
	unsigned int *vec =	createfVector(fileBuffer);

	// cria arvore usando o vetor de pesos
	struct listHeader *lista_de_pesos = vectorToListOfTrees(vec);
	free(vec); // libera vetor
	// printf("\n-----> printLista:\n"); 													//debug
	// printList(lista_de_pesos); 																	//debug
	struct tree *raiz_da_arvore = makePathTree(lista_de_pesos);
	// printf("\n-----> printTree:\n");  													//debug
	// printTree(raiz_da_arvore);
	// printf("\n"); 			 																				//debug

	// cria tabela dos caminhos
	// printf("\n-----> \tcreateTable\n");													//debug
	unsigned char pathTable[NCHARS][9];
	for(int o = 0; o < NCHARS; o++) for(int p = 0; p < 9; p++) // zera a matriz
		pathTable[o][p] = 0;
	unsigned char v[9];
	for(int o = 0; o < NCHARS; o++)	v[o] = 0; //zera o vetor
	createTable(raiz_da_arvore, pathTable, v, 0);
	
	// imprime a tabela de conversão
	for(int o = 0; o < NCHARS; o++){ 														//debug
		if(pathTable[o][0] != '\0'){															//debug
			printf("\n'%03d':", o);
			printf("%s", pathTable[o]);
		}
	}																														//debug
	
	// escreve o arquivo compactado (binário)
	printf("\n\n-----> \twriteHeader:\n");											//debug
	unsigned char *header = writeHeader(raiz_da_arvore);
	printf("\n\n-----> \twriteBody:\n");												//debug
	unsigned char *body =	writeBody(pathTable, fileBuffer);
	writeToFile(FILENAME_OUT_C, header, body);

	// ..and now W. Wallace would like to call for freedom:
	free(fileBuffer);
	freeList(lista_de_pesos);
	freeTree(raiz_da_arvore);
	free(header);
	free(body);
	return 0;
}

// TODO: função que descompacta
int descompacta(const char *filename)
{
	return 0;
}

// mostra ajuda
void help(){
	printf("Este programa utiliza o algorítimo de Huffman para compactar e \n descompactar arquivos.\n");
	printf("Modo de uso:\n");
	printf("\t -c\t [arquivo]\t compacta \n");
	printf("\t -d\t [arquivo]\t descompacta \n");
}

////////////////////////////////////////////////////////////////////////////////
// funções de árvore
////////////////////////////////////////////////////////////////////////////////

// cria a árvore
struct tree *createTree(int mf, char mc, struct tree *l,
  struct tree *r)
{
	struct tree *mtree = (struct tree*)malloc(sizeof(struct tree));
	(*mtree).f = mf;
	(*mtree).c = mc;
	(*mtree).r = r;
	(*mtree).l = l;
	// printf("createTree: %d,%c,%p,%p\n", (*mtree).f,(*mtree).c,(*mtree).r,(*mtree).l); //debug

	return mtree;
}

// imprime a árvore (travessal mode)
void printTree(struct tree *mtree)
{
	if (mtree!=NULL) printf("<%d[%c]",(*mtree).f, (*mtree).c);
	else printf("<>");
	if ((*mtree).l!=NULL) printTree((*mtree).l);
	else printf("<>");
	if ((*mtree).r!=NULL) printTree((*mtree).r);
	else printf("<>");
	printf(">");
}

// libera a árvore
void freeTree(struct tree *mtree)
{
	if((*mtree).l != NULL) freeTree((*mtree).l);
	if((*mtree).r != NULL) freeTree((*mtree).r);
	free(mtree);
}

////////////////////////////////////////////////////////////////////////////////
// funções de lista
////////////////////////////////////////////////////////////////////////////////

// cria a lista
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

// insere elemento em ordem crescente
struct listHeader *insertSortedList(struct listHeader *mlH, struct tree *mtree)
{
	// caso inicial, quando a lista foi inicializada com nulo
	if( (*(*mlH).start).tree == NULL ){
		(*(*mlH).start).tree = mtree;
		(*(*mlH).start).next = NULL;
	}else{
		struct list *p = (*mlH).start; //ponteiro que percorre a lista

		// cria novo nó
		struct list *novo = (struct list*)malloc(sizeof(struct list));
		(*novo).next = NULL;
		(*novo).tree = mtree;

		if( (*(*novo).tree).f < (*(*(*mlH).start).tree).f ){
			// insere no início
      (*novo).next = (*mlH).start;
      (*mlH).start = novo;
      (*mlH).size++;
    }else for(p = (*mlH).start; ; p = (*p).next){ // percorre a lista
      if( (!(*p).next) || ((*(*(*p).next).tree).f > (*(*novo).tree).f) ){
				// insere no meio ou no fim
				(*novo).next = (*p).next;
				(*p).next = novo;
				(*mlH).size++;
				break;
      }
    }
	}

	return mlH;
}

// imprime a lista
void printList(struct listHeader *mlist)
{
	struct list *mmlist = (*mlist).start;
	for(int i=0; i<(*mlist).size; i++){
		printf("\t%03d::%03d, %03d\n", i, (*(*mmlist).tree).f, (*(*mmlist).tree).c);
		mmlist = (*mmlist).next;
	}
	printf("\n");
}

// libera a lista
void freeList(struct listHeader *mlH)
{
	struct list *mlist1 = (*mlH).start;
	struct list *mlist2;
	for (int i=0; i < (*mlH).size; i++){
		mlist2 = (*mlist1).next;
		free(mlist1);
		mlist1 = mlist2;
	}
	free(mlH);
}

////////////////////////////////////////////////////////////////////////////////
// funções de vetor
////////////////////////////////////////////////////////////////////////////////

// insere ordenado no vetor
void insertionSortVector(int *v, unsigned int n)
{
	int i, j, tmp;
	for(i=0;i<n;i++){
		tmp = v[i];
		for(j=i-1;j>=0 && tmp<v[j];j--) v[j+1] = v[j];
		v[j+1] = tmp;
	}
}

// cria vetor de pesos
unsigned int *createfVector(unsigned char *buffer)
{
	unsigned int *u = (unsigned int*)calloc(NCHARS, sizeof(unsigned int));
	for(int i = 0; buffer[i]; i++) u[buffer[i]]++;
	u[ENDOFFILE]++; // adiciona o caracter de fim de arquivo
	return u;
}

////////////////////////////////////////////////////////////////////////////////
// funções de arquivo
////////////////////////////////////////////////////////////////////////////////

// le do arquivo para a memória
// ref: http://www.fundza.com/c4serious/fileIO_reading_all/
unsigned char *readFileToBuffer(const char *filename)
{
	FILE *fp;
	unsigned char *buffer;
	unsigned long long int n;

	fp = fopen(filename, "r");
	if(fp == NULL){
		printf("ERRO: Sem permissões de leitura ou o arquivo não encontrado.\n");
		exit(EXIT_FAILURE);
	}

	fseek(fp, 0L, SEEK_END); // Conta o número de bytes do arquivo
	n = ftell(fp);
	fseek(fp, 0L, SEEK_SET);	// Retorna ao inínio

	buffer = (unsigned char*)calloc(n+1, sizeof(unsigned char)); //
	if(!buffer){
		printf("ERRO: Memória insuficiente.\n");
		exit(EXIT_FAILURE);
	}

	fread(buffer, sizeof(char), n, fp); // Copia o arquivo pro buffer

	printf("O conteúdo do arquivo lido foi:\n“%s”\n", buffer);			//debug

	fclose(fp);
	return buffer;
}

// escreve no arquivo
void writeToFile(char *filename, unsigned char *header, unsigned char *body)
{
	// escreve no arquivo
	FILE *fp = fopen(filename, "w");
	if(fp == NULL){
		printf("ERRO: Sem permissões de leitura ou espaço insuficiente.\n");
		exit(EXIT_FAILURE);
	}
	// TODO: encontrar a quantidade de bytes à escrever!
	fwrite(header, sizeof(header), 1+strlen((char*)header), fp);
	fwrite(body, sizeof(body), strlen((char*)body), fp);
	fclose(fp);
}

////////////////////////////////////////////////////////////////////////////////
// funções do algoritimo de huffman
////////////////////////////////////////////////////////////////////////////////

// cria lista de arvores de um dado vetor de pesos
struct listHeader *vectorToListOfTrees(unsigned int *v)
{
	// printf("\nvectorToListOfTrees:\n"); 												//debug
	struct listHeader *mlH = createList(NULL); //cria lista
	for(int i = 0; i < NCHARS; i++)
		if( (v[i] != 0) && (v[i] < NCHARS) ){
			// printf("%d>", i); 																			//debug
			struct tree *mtree = createTree(v[i], i, NULL, NULL);
			insertSortedList(mlH, mtree);
		}

	return mlH;
}

// cria arvore de huffman a partir da lista de arvores
struct tree *makePathTree(struct listHeader *mlH)
{
	// printf("\nmakePathTree:\n"); 																//debug
	struct list *mlist1 = NULL;;
	struct list *mlist2 = NULL;
	struct tree *mtree = NULL;;
	int size = (*mlH).size;

	for(int i = 0; i < size -1; i++){
		// printf("start: %p,end: %p\n", (*mlH).start, (*mlH).end);  //debug
		// printf("\t\tsize:::%d:::%d\n", (*mlH).size, i); 					//debug

		mlist1 = (*mlH).start;
		mlist2 = (*(*mlH).start).next;

		// cria um novo nó contendo como filhos os dois primeiros da lista ordenada
				// e insere ordenadamente como um novo item da lista
		mtree = createTree(
			(*(*mlist1).tree).f + (*(*mlist2).tree).f,
			'\0',
			(*mlist1).tree, (*mlist2).tree
		);

		// printf("\t %d: %d\n", (*mtree).c, (*mtree).f ); 				//debug

		mlH = insertSortedList(mlH, mtree);

		// remove e atualiza o cabeçalho
		if((*mlist2).next==NULL) break;
		(*mlH).start = (*mlist2).next;
		free(mlist2);
		(*mlH).size--;
		(*mlH).size--;
		free(mlist1);
	}

	return mtree;
}

// cria a tabela de conversão
void createTable(struct tree *mtree,
	unsigned char pathTable[][9],
	unsigned char *v,
	unsigned char i
){
	if((*mtree).l!=NULL){
		v[i] = '0';
		createTable((*mtree).l, pathTable, v, ++i);
		i--;
	}
	if((*mtree).r!=NULL){
		v[i] = '1';
		createTable((*mtree).r, pathTable, v, ++i);
		i--;
	}
	if(((*mtree).r==NULL) && ((*mtree).r==NULL)){
		v[i] = '\0'; // delimita a string
		// chegou à folha, entao escreve associado à posição da matriz
		for(int k = 0; k < 9; k++) pathTable[(int)(*mtree).c][k] = v[k];
	}
}

// escreve o cabeçalho do arquivo.
unsigned char *writeHeader(struct tree *mtree)
{
	// TODO: verificar e modificar tamanho!!!
	unsigned char *header = (unsigned char*)calloc(NCHARS+32, sizeof(unsigned char));
	int i = 0;
	createHeader(mtree, header, &i);

	// 32 bits 0 marcam o fim do header
	for(int j = 0; j < 4; j++) header[i+j] = 0;
	for(int i = 0; i < strlen((char*)header)+32; i++)
		printf("%02X ", header[i]); 													//debug
	
	return header;
}

void createHeader(struct tree *mtree, unsigned char *header, int *i)
{
	if((*mtree).l) createHeader((*mtree).l, header, i);
	if((*mtree).r) createHeader((*mtree).r, header, i);
	if((!(*mtree).r) && (!(*mtree).r)){
		// formato: 	(f)   (char)   (f)   (char) (f nula)
		//  					32b  |  8b  |  32b  |  8b  |  0x00
		// tamanho maximo: createHeader256b+32b = 288b
		// fuencia máxima por char: 2^32
		header[(*i)] = (unsigned char)(((*mtree).f >> 16) & 0xFFFF);
		header[(*i)++] = (unsigned char)((*mtree).f & 0xFFFF);
		header[(*i)++] = (*mtree).c;
	}
}

// limita o valor de 0 a 8 (1Byte). Aqui foi utilizado um branch
// prediction executado em tempo de compilação.
int for1BLim(int x)
{
  if(likely(x>7)) return x-8;
  else return x;
}

// transforma uma string em um binário
void stringToBinary(char* x, char* texto)
{
  for(int i=0; i<strlen(x); i++)
    texto[(int)(i/8)] = 
    (texto[(int)(i/8)] | ( (x[i] & 0x1) << (7 -for1BLim(i)) )) & 0xff;
}

// Imprime em binário
void printBinary(int x)
{
  for(int i=0; i<8; i++) printf("%d", (x >> (7-i)) & 0x1);
}

// cria o corpo do arquivo fileBuffer codificado pela tabela pathTable,
// já adicionando o fim do arquivo.
unsigned char *writeBody(unsigned char pathTable[][9],
	unsigned char *fileBuffer)
{
	int a = (int)strlen((char*)fileBuffer); // tamanho do fileBuffer
	int b; // tamanho da string do código de conversão (pathTable[i])
	
	unsigned char *encodedText = (unsigned char*)calloc(NCHARS,a);
	unsigned char path[9]; // armazena o caminho para um dado caracter
	
	// pega o código de huffman (guarda em path) para cada char do 
	// fileBuffer e concatena todos os caminhos no encodedText.
	for(int i = 0, j; i < a; i++){
		b = strlen((char*)pathTable[ fileBuffer[i] ]); // pega o tamanho
		for(j = 0; j < b; j++){
			path[j] = pathTable[ fileBuffer[i] ][j]; // pega o caminho
			path[j+1] = 0; // delimita a string
		}
		strcat((char*)encodedText, (char*)path); // concatena
	}
	
	// adiciona o fim do arquivo, tratando já caso o tamanho não for inteiro
	b = strlen((char*)pathTable[ENDOFFILE]);
	for(int j = 0; j < b; j++){
		path[j] = pathTable[ENDOFFILE][j]; // pega o caminho
		path[j+1] = 0; // delimita a string
	}
	int i = strlen((char*)encodedText)%8;
	if(!i) i = 8;
	for(; i >= 0; i--)	strcat((char*)encodedText, (char*)path);
	
	// printf("encodedText: %s\n", encodedText); 							// debug

	// aloca enfim a variável que amazena o binário
	unsigned char *body = (unsigned char*)calloc(NCHARS,a);
	
	// converte a string de encodedText para um binário
  stringToBinary((char*)encodedText, (char*)body);
	
	// debug	
	for(int i=0; i<strlen((char*)encodedText)/8; i++ ) printBinary((int)body[i]);
  putchar('\n');
	
	free(encodedText); // libera
	return body;
}






////////////////////////////////////////////////////////////////////////////////
