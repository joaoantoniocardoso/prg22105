#include <stdio.h>
#include <string.h>

void batata(char x, char* texto, unsigned int start)
{
  for(char i=0; i<8;i++)
    texto[start+(7-i)]=(x>>i & 0x1);
}

int main()
{
  char* texto = "101100";
  char resultado[strlen(texto)*8];

  printf("[original] %s\n",texto);
  printf("tamanho do texto original %d\n", (int)strlen(texto) );
  for(int i=0; i<strlen(texto); i++ )
  {
    batata(texto[i], resultado, i*8);
  }
  printf("[resultado] ");
  for(int i=0; i<strlen(texto)*8; i++ )
    printf("%d",(int)resultado[i]);
  printf("\n");
  return 0;
}