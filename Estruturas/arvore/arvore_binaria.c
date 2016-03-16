#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct arvore
{
	struct arvore *direita;
	struct arvore *esquerda;
	int valor;
}; 

//funcoes
struct arvore *criar_arvore(int valor_inicial, struct arvore *esquerda, struct arvore *direita);
void imprime_arvore(struct arvore *marvore);
void libera_arvore(struct arvore *marvore);
// void remove_arvore(struct arvore *marvore);
struct arvore *cria_arvore_ordenado(int *v, int n);
struct arvore *busca_recursiva_arvore_ordenada(struct arvore *marvore, int i);
int profundidade_arvore(int size);
int conta_arvore(struct arvore *marvore, int i);
struct arvore *transforma_vetor_em_arvore_binaria(struct arvore *arv, int *v, int min, unsigned int v_size);
int transforma_arvore_binaria_em_vetor(struct arvore *marvore, int v[], int i);
int inserir_ordenado_no_vetor(int *v, int size_v, int i);

struct arvore *inserir_ordenado_arvore(struct arvore *arv, int i);

//exercicios
void exercicio1();
void exercicio_inserir_ordenado();

int main(){
	// exercicio1();
	printf("%d\n", profundidade_arvore(2));
	exercicio_inserir_ordenado();
	return 0;
}

struct arvore *inserir_ordenado_arvore(struct arvore *arv, int i){
	int arvore_size = conta_arvore(arv, 0);
	int v[arvore_size];

	transforma_arvore_binaria_em_vetor(arv, v, 0);
	arvore_size = inserir_ordenado_no_vetor(v, arvore_size, i);
	libera_arvore(arv);
	arv = transforma_vetor_em_arvore_binaria(arv, v, 0, arvore_size);
	return arv;
}

struct arvore *transforma_vetor_em_arvore_binaria(int *v, int min, unsigned int v_size){
	unsigned int a=0, b=v_size;
	struct arvore *arvd, *arve;
	
	for(int n=v_size/2;(min!=b-1);n=(b+min)/2){
		(*arv).valor = v[n];
		(*arv).direita = transforma_vetor_em_arvore_binaria(arv, v, min, v_size);
		a=n;
	}
	for(int n=v_size/2;(min!=b-1);n=(b+min)/2){
		(*arv).valor = v[n];
		(*arv).esquerda = transforma_vetor_em_arvore_binaria(arv, v, min, v_size);
		b=n;
	}
	return arv;
}

int *binarySearchIntVector(int *v, unsigned int n, int value){
	unsigned int a=0, b=n;
	for(n=b/2;(a!=b-1);n=(b+a)/2){
		if(v[n]==value) return &v[n]; //encontrado
		else if(v[n]<value) a=n;
		else b=n;
	}
	return NULL; //nao encontrado
}

/*
	marvore é a arvore, v[] é o vetor,
	i é numero de elementos que foram inseridos,
	deve chamar a função com i=0
*/
int transforma_arvore_binaria_em_vetor(struct arvore *marvore, int v[], int i){
	if(marvore == NULL) return i;
	v[i] = (*marvore).valor;
	i++;
	if((*marvore).esquerda != NULL) i = transforma_arvore_binaria_em_vetor((*marvore).esquerda, v, i);
	if((*marvore).direita != NULL) i = transforma_arvore_binaria_em_vetor((*marvore).direita, v, i);
	return i;
}

int inserir_ordenado_no_vetor(int *v, int size_v, int i){
	int j = size_v-1;
	for(; i < v[j] && j>=0; j--) v[j+1] = v[j];
	v[j+1] = i;
	return size_v++;
}

/*
	i é numero de elementos que foram inseridos,
	deve chamar a função com i=0
*/
int conta_arvore(struct arvore *marvore, int i){
  if (marvore == NULL) return 0;
	i++;
  if((*marvore).esquerda != NULL) i = conta_arvore((*marvore).esquerda, i);
  if((*marvore).direita != NULL) i = conta_arvore((*marvore).direita, i);
  return i;
}

void exercicio_inserir_ordenado(){
	int v[] = {1,2,3,4,5,6,7,8,9,10},
			v_size = sizeof(v)/sizeof(*v);
	struct arvore *arv1 = transforma_vetor_em_arvore_binaria(v, v_size, 0, );
	// (struct arvore *arv, int *v, int min, unsigned int v_size)

	for(int i=0; i<v_size; i++){
		// inserir_arvore(arv1, v[i]);
	}

}

// testar
struct arvore *busca_recursiva_arvore_ordenada(struct arvore *marvore, int i){
	if((*marvore).valor == i) return marvore;
	else{
		if((*marvore).valor > i){
			if((*marvore).direita != NULL)  busca_recursiva_arvore_ordenada((*marvore).direita, i);
			else return NULL;
		}else{ // entao marvore < i
			if((*marvore).esquerda != NULL)  busca_recursiva_arvore_ordenada((*marvore).esquerda, i);
			else return NULL;
		}
	}
	return NULL;
}

//retorna a profundidade da arvore ordenada para um dado numero de elementos
// return pow(2,(size+1))-1;
int profundidade_arvore(int size){
	return size; //TODO
}

struct arvore *criar_arvore(int valor_inicial, struct arvore *esquerda, struct arvore *direita){
	struct arvore *marvore = (struct arvore*)malloc(sizeof(struct arvore));
	(*marvore).valor = valor_inicial;
	(*marvore).direita = direita;
	(*marvore).esquerda = esquerda;

	return marvore;
}

void imprime_arvore(struct arvore *marvore){
	if (marvore!=NULL) printf("<%c", (*marvore).valor);
	else printf("<>");
	if ((*marvore).esquerda!=NULL) imprime_arvore((*marvore).esquerda);
	else printf("<>");
	if ((*marvore).direita!=NULL) imprime_arvore((*marvore).direita);
	else printf("<>");
	printf(">");
}

void libera_arvore(struct arvore *marvore){
	if((*marvore).esquerda != NULL) libera_arvore((*marvore).esquerda);
	if((*marvore).direita != NULL)  libera_arvore((*marvore).direita);
	free(marvore);
}

void exercicio1(){
	struct arvore *arv1, *arv2, *arv3, *arv4, *arv5, *arv6;

	arv1 = criar_arvore('f',NULL,NULL);
	arv2 = criar_arvore('d',NULL,NULL);
	arv3 = criar_arvore('e',NULL,NULL);
	arv4 = criar_arvore('b',NULL,arv2);
	arv5 = criar_arvore('c',arv3,arv1);
	arv6 = criar_arvore('a',arv4,arv5);

	imprime_arvore(arv6);
	libera_arvore((void*)arv6);
	// imprime_arvore(arv6);

	printf("\nfim.\n");
}
