// compilar com -fopenmp -Dmp
#include <stdio.h>
#include <string.h>

// branch prediction via compilador
#define likely(x)       __builtin_expect((x),1)
#define unlikely(x)     __builtin_expect((x),0)

// limita o valor de 0 a 8 (1Byte). Aqui foi utilizado um branch prediction
// executado em tempo de compilação.
int for1BLim(int x)
{
  if(likely(x>7)) return x-8;
  else return x;
}
int for1BLimP(int x)
{
  if(x>7) return x-8;
  else return x;
}

// transforma uma string em um binário (utilizando processamento paralelo total)
// compilar com -fopenmp -Dmp
// como temos variáveis comparilhadas ('texto' por ex) não podemos utilizá-lo
// sem um tratamento adequado, mas fica como um exemplo de primeiro contato.
void stringToBinaryP(char* x, char* texto)
{
  #ifdef mp
    #pragma omp parallel for
  #endif
  for(int i=0; i<strlen(x) ;i++)
    texto[(int)(i/8)] = 
    (texto[(int)(i/8)] | ( (x[i] & 0x1) << (7 -for1BLimP(i)) )) & 0xff;
}

void stringToBinary(char* x, char* texto)
{
  for(int i=0; i<strlen(x) ;i++)
    texto[(int)(i/8)] = 
    (texto[(int)(i/8)] | ( (x[i] & 0x1) << (7 -for1BLim(i)) )) & 0xff;
}

// Imprime em binário
void printBinary(int x)
{
  for(int i=0; i<8; i++) printf("%d", (x >> (7-i)) & 0x1);
}

int main()
{
  char* texto = "10110000";
  printf("[original] %s\n",texto);
  printf("tamanho do texto original %d, multiplo de 8 ? (%d)\n",
    (int)strlen(texto), (int)(strlen(texto)%8+1)%2);
    
  if(strlen(texto)%8) return 0;

  char resultado[strlen(texto)/8];
  memset(&resultado[0], 0x0, sizeof(resultado));
  stringToBinary(texto, resultado);
  
  printf("[resultado] ");
  for(int i=0; i<strlen(texto)/8; i++ )
    printBinary((int)resultado[i]);
  printf("\n");
  
  return 0;
}