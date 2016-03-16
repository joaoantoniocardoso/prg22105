#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FILENAME "num.txt"

// gera um vetor de tamanho n com inteiros únicos
void randUniqueIntVector(int *v, int n);
// escreve um vetor de inteiros para um arquivo
void writeVectorToFile(int *v, int n);

int main(){
  int *v, i;

  printf("Este programa gera um arquivo de texto contendo inteiros únicos e aleatórios. Entre com a quantidade de números a serem gerados: ");
	scanf("%d", &i);

	v = (int*)malloc(sizeof(int)*(i));

  randUniqueIntVector(v,i);
  writeIntVectorToFile(v,i);

  free(v);
  return 0;
}

void writeIntVectorToFile(int *v, int n){
  FILE *fp;
  fp = fopen(FILENAME, "w+");
  if (fp == NULL){
		printf("Desculpe, houve um erro ao tentar criar o arquivo.");
		exit(-1);
	}else{
    while(n>0){
      fprintf(fp, "%d,", v[n]);
      n--;
    }
  }
}

void randUniqueIntVector(int *v, int n){
  int i=0, j, a=0, b;
  srand((unsigned)time(NULL));
	while(i<n){
    a = rand()%n+1;
    for(b=j=0;j<n;j++) if(a==v[j]) b=1;
    if(b==0){
      v[i] = a;
      i++;
    }
  }
}
