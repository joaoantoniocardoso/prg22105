#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

void randVector(int *v, int n);
void duplicaVetor(int *a, int *b, int n);
void printVector(int *v, int n);
void troca(int *a, int *b);
int encontraMenor(int *v, int n, int index);
void bubbleSort_vect(int *v, int n);
void selectionSort_vect(int *v, int n);
void insertionSort_vect(int *v, int n);

int main(){
	int i, *u, *v, *w;
	clock_t inicio, fim; /* ref:http://www.gnu.org/savannah-checkouts/gnu/libc/manual/html_node/CPU-Time.html#CPU-Time */

	printf("Entre com o tamanho desejado para o vetor de inteiros aleatorios ser gerado: ");
	scanf("%d", &i);

	u = (int*)malloc(sizeof(int)*(i));
	v = (int*)malloc(sizeof(int)*(i));
	w = (int*)malloc(sizeof(int)*(i));


	randVector(u,i);
	duplicaVetor(u,v,i);
	duplicaVetor(u,w,i);

	printf("Foram criados três vetores idênticos para a comparação entre os algorítimos de ordenação. \nO tempo de execução para cada um dos algorítimos foi: \n");

	inicio = clock();
	bubbleSort_vect(u,i);
	fim = clock();
	printf("Bubble Sort: \t%lf segundos.\n", ((double) (fim-inicio))/CLOCKS_PER_SEC);

	inicio = clock();
	selectionSort_vect(v,i);
	fim = clock();
	printf("Selection Sort: %lf segundos.\n", ((double) (fim-inicio))/CLOCKS_PER_SEC);

	inicio = clock();
	insertionSort_vect(w,i);
	fim = clock();
	printf("Insertion Sort: %lf segundos.\n", ((double) (fim-inicio))/CLOCKS_PER_SEC);

	free(v);
	free(u);
	free(w);
	u=v=w=NULL;
	return 0;
}

void randVector(int *v, int n){
	int i;
	srand((unsigned)time(NULL));
	for(i=0;i<n;i++) v[i] = rand()%100;
}

void printVector(int *v, int n){
	int i;
	for(i=0;i<n;i++){
		printf("%d\t", *v);
		v++;
	}
	v-=(i); //rebobina
	printf("\n");
}

void troca(int *a, int *b){
	int tmp = *b;
	*b = *a;
	*a = tmp;
}

void bubbleSort_vect(int *v, int n){
	int i;
	for(n--;n>0;n--)
		for(i=0;i<n;i++)
			if(v[i]>v[i+1]) troca(&v[i],&v[i+1]);
}

int encontraMenor(int *v, int n, int index){
	int i, min;
	for(i=index+1,min=index;i<n;i++)
		if(v[i]<v[min]) min = i;
	return min;
}

void selectionSort_vect(int *v, int n){
	int i;
	for(i=0;i<n-1;i++) troca(&v[i],&v[encontraMenor(v,n,i)]);
}

void insertionSort_vect(int *v, int n){
	int i, j, tmp;
	for (i=0;i<n;i++){
		tmp = v[i];
		j = i-1;
		for(;j>=0 && tmp<v[j];j--) v[j+1] = v[j];
		v[j+1] = tmp;
	}
}

void duplicaVetor(int *a, int *b, int n){
	int i;
	for(i=0;i<n;i++) b[i] = a[i];
}
