// compilar com g++ -fopenmp -Dmp -std=c++14
#include <stdio.h>
#include <string.h>

auto batata2 = [](char x, char* texto, unsigned int start)
{
  #ifdef mp
    #pragma omp parallel for
  #endif
  for(char i=0; i<8;i++)
    texto[start+(7-i)]=(x>>i & 0x1);
};

void batata(char x, char* texto, unsigned int start)
{
  #ifdef mp
    #pragma omp parallel for
  #endif
  for(char i=0; i<8;i++)
    texto[start+(7-i)]=(x>>i & 0x1);
}

int main()
{
  char* texto = "joao doidjo";
  char resultado[strlen(texto)*8];

  printf("[original] %s\n",texto);
  printf("tamanho do texto original %d\n",strlen(texto) );

  #ifdef mp
    #pragma omp parallel for
  #endif
  for(int i=0; i<strlen(texto); i++ )
    batata2(texto[i], resultado, i*8);

  printf("[resultado] ");
  for(int i=0; i<strlen(texto)*8; i++ )
    printf("%d",(int)resultado[i]);
  printf("\n");
  return 0;
}