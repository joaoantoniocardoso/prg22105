// Questão 3:
// Implementar uma função em C, a qual receba o nome  de um arquivo e uma
// "senha chave" de seis (06) números, essa função de gerar um arquivo
// criptografado e salva-lo com o nome: "nome_do_arquivo_original.cfr".
// Ex. int crypto1("meuarquivo.txt", 123456);
// meuarquivo.txt ={"oi este é o texto a ser criptografado"}
// 1º A função deve obrigatoriamente ler o arquivo e salvar cada palava em nó de
// uma lista.
// 2º Fazer a criptografia da seguinte forma:
// Lista      "oi"      "este"            "é"   "o"   ...
// em ASCII   111 105   101 115 116 101   130   111   ...
// Chave      1         2                 3     4     ...
// Resultado  112 106   103 117 118 103   133   115
// Resultado  pj        guvg              à     s
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

////////////////////////////////////////////////////////////////////////////////
// funções de error
////////////////////////////////////////////////////////////////////////////////

void erralloc()
{
	printf("Error: insufficient memory.\n");
	exit(EXIT_FAILURE);
}

////////////////////////////////////////////////////////////////////////////////
// funções de lista
////////////////////////////////////////////////////////////////////////////////

struct list
{
	char *word;
	struct list *next;
};

// insere no fim da lista
struct list *insertList(struct list *mlist, char *c)
{
	struct list *nlist  = (struct list*)malloc(sizeof(struct list));
	if(!nlist) erralloc();
	(*nlist).next = NULL;
	(*nlist).word = calloc(strlen(c) +1, sizeof(char));
	if(!(*nlist).word) erralloc();
	strcpy((*nlist).word, c);

	if(mlist){
		// encontra o ultimo item
		struct list *olist = mlist;
		while((*olist).next) olist = (*olist).next;

		// insere após o últiomo
		(*olist).next = nlist;
		return mlist;
	}else	return nlist;
}

void freeList(struct list *mlist)
{
	for(struct list *nlist; mlist; mlist = nlist){
		nlist = (*mlist).next;
		free((*mlist).word);
		free(mlist);
	}
	free(mlist);
}

void printList(struct list *mlist)
{
	for(; mlist; mlist = (*mlist).next)
		printf("'%s' ", (*mlist).word);
	putchar('\n');
}

////////////////////////////////////////////////////////////////////////////////
// funções de arquivo
////////////////////////////////////////////////////////////////////////////////

char *readFile(char *filename)
{
	FILE *fp;
	char *buffer;
	unsigned long long int n;

	fp = fopen(filename, "r");
	if(!fp){
		printf("Error: file not found or it isn't acessible.\n");
		exit(EXIT_FAILURE);
	}

	fseek(fp, 0L, SEEK_END); // Conta o número de bytes do arquivo
	n = ftell(fp);
	fseek(fp, 0L, SEEK_SET); // Retorna ao inínio

	buffer = (char*)calloc(n+1, sizeof(char));
	if(!buffer) erralloc();

	fread(buffer, sizeof(char), n, fp); // Copia o arquivo pro buffer

	fclose(fp);
	return buffer;
}

int writeFile(char *filename, char *buffer){
	// muda a extensão do arquivo de saída
	char ext[] = ".cfr";
	strtok(filename, ".");
	strcat(filename, ext);

	// substitui ou cria o arquivo
	FILE *fp = fopen(filename, "w");
	if(!fp) erralloc();

	// escreve
	fwrite(buffer, sizeof(char), strlen(buffer), fp); // Do buffer pro arquivo

	// fecha
	fclose(fp);
	return 0;
}

int crypto1(char *filename, char *key)
{
	char *rawText = readFile(filename);
	char *word;
  char *encryptedText = calloc(strlen(rawText)+1, sizeof(char));
	if(!encryptedText) erralloc();
	
	printf("%s\n", rawText);

	word = strtok(rawText, " "); // pega a primeira palavra
	struct list *words = insertList(NULL, rawText); // inicia a lista

	while((word = strtok(NULL, " "))) // pega as outras palavras
		words = insertList(words, word);

  int i,j;
	struct list *tmp = words;
	char ctmp[2] = "'";
	for (j=0 ;;){
		// soma o valor da chave à cada letra da palavra da lista
		for(i=0; (*tmp).word[i]; i++){
			ctmp[0] = (*tmp).word[i] + (key[j]-48);
			encryptedText = strcat(encryptedText, ctmp);
		}
		// recicla
		if(j >= strlen(key)-1) j=0;
		else j++;
		if(!(*tmp).next) break;
		tmp = (*tmp).next;
		// adiciona um espaço entre as palavras
		ctmp[0] = ' ';
		encryptedText = strcat(encryptedText, ctmp);
	}

  // salvar em arquivo encriptado
	writeFile(filename, encryptedText);

	freeList(words);
  free(rawText);
  free(encryptedText);
  return 0;
}

////////////////////////////////////////////////////////////////////////////////
// outras
////////////////////////////////////////////////////////////////////////////////

void help()
{
  printf("\
Usage: q3 [FILE]... [KEY]...\n\
Encrypt the FILE (the current directory by default) using the KEY passed. \n\n\
As an illustrative example If you call < q3 test.txt 123456 > it will take \n\
the text of test.txt that, e.g. contains the text 'encrypt me please', that \n\
in ASCII is:\n\
\t'101 110 099 114 121 112 116 032 109 101 032 112 108 101 097 115 101', \n\
the file ASCII encrypted would be:\n\
\t'102 111 100 115 122 113 117 032 111 103 032 115 111 104 100 118 104', \n\
that actually means 'fodszqu og sohdvh'.\n\n\
\t\t\t\t\t Made by github.com/joaoantoniocardoso\n");
}

////////////////////////////////////////////////////////////////////////////////
// main
////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
  if(argc<3) help();
	else return crypto1(argv[1], argv[2]);
	return 0;
}
