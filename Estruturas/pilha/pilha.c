#include <stdio.h>
#include <stdlib.h>

struct dados{
	char c;
};

struct itempilha{
	struct dados *dado;
	struct itempilha *proximo;
};

struct pilha{
	struct itempilha *start;
	int size;
};

//cria uma pilha com um elemento nulo
struct pilha* criarpilha(){
	//cria pilha
	struct itempilha *mitempilha = (struct itempilha*)malloc(sizeof(struct itempilha));
	(*mitempilha).dado = NULL;
	(*mitempilha).proximo = NULL;

	//cria cabecalho
	struct pilha *mpilha = (struct pilha*)malloc(sizeof(struct pilha));
	(*mpilha).size = 1;
	(*mpilha).start = mitempilha;

	return mpilha;
}

//grava dados_inicial
int push(struct pilha *mpilha, char dado_inicial){
	struct itempilha *novo_elemento = (struct itempilha*)malloc(sizeof(struct itempilha));
	struct dados *mdado = (struct dados*)malloc(sizeof(struct dados));
	(*mdado).c = dado_inicial;
	(*novo_elemento).dado = mdado;
	(*novo_elemento).proximo = (*mpilha).start;
	(*mpilha).start = novo_elemento;
	(*mpilha).size++;
	
	return 0;
}


//remove ultimo e retorna o dado atraves do ponteiro passado *mdado
int pop(struct pilha *mpilha, struct dados *mdado){
	struct itempilha *elemento = (struct itempilha*)malloc(sizeof(struct itempilha));
	elemento = (*mpilha).start;
	(*mpilha).start = (*elemento).proximo;
	(*mpilha).size--;
	mdado = (*elemento).dado; //Retorno por ref.
	free((*elemento).dado);
	free(elemento);

	return 0;
}

void imprimir_pilha(struct pilha *mpilha){
	printf("A sua pilha é: ");
	struct itempilha *mitempilha = (*mpilha).start;
	while((*mitempilha).proximo !=NULL){
		printf("%c, ", (*(*mitempilha).dado).c);
		mitempilha = (*mitempilha).proximo;
	}
}

//retorna a profundidade na pilha que se encontra o elemento buscado
//NAO ESTA FUNCIONANDO. segmentation fault se acessa (*(*(*mitempilha).proximo).dado).c 
int busca_elemento_pilha(struct pilha *mpilha, char mchar){
	struct itempilha *mitempilha = (*mpilha).start;
	int i;
	printf("Buscando...");
	for(i=0;(*mitempilha).proximo !=NULL;i++){
		// if( (*(*(*mitempilha).proximo).dado).c == mchar ) return i;
		printf(".");
		mchar = ;
		printf("%c",mchar);
		mitempilha = (*mitempilha).proximo;
	}

	return -1;
}

int main(void){
	char ctemp[50];
	printf("Insira uma frase para ser invertida de ate 50 caracteres\n");
	scanf("%[^\n]s", ctemp);
	getchar();
	struct pilha *pilha1 = criarpilha();
	int i;
	for (i = 0; i<sizeof(ctemp); ++i){
		if (ctemp[i]=='\0') break;
		printf("%c ,", ctemp[i]);
		push(pilha1, ctemp[i]);
	}
	printf("lidos %d caracteres\n", i);
	imprimir_pilha(pilha1);
	
	//testando o pop
	printf("\n\t\t\t\t\tPOP~~\n");
	struct dados *mdado = (struct dados*)malloc(sizeof(struct dados));
	pop(pilha1, mdado);
	imprimir_pilha(pilha1);
	free(mdado);

	getchar();
	char c;
	//testando busca
	printf("\nEntre com um caractere para saber a profundidade na pilha: ");
	c = getchar();
	// scanf("%c", c);
	i = busca_elemento_pilha(pilha1, c);
	if(i==-1) printf("\nNenhum caracter %c enecontrado\n", c);
		else printf("\nO caractere %c foi encontrado na posicao %u \n", i);


	// verificando endereços de memória dos apontamentos e seus valores
	// printf("\n\t\t\t\t\t %u -> %u -> %u \t\t\t", (*pilha1).start, (*(*pilha1).start).proximo, (*(*(*pilha1).start).proximo).proximo);
	// printf("\n\t\t\t\t\t %c -> %c -> %c \t\t\t",
	// 		(*(*(*pilha1).start).dado).c, 
	// 		(*(*(*(*pilha1).start).proximo).dado).c, 
	// 		(*(*(*(*(*pilha1).start).proximo).proximo).dado).c);

	return 0;
}