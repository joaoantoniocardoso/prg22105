// Questão 2:
// Implementar em C uma função que receba um número, converta-o em binário, e
// inverta esse número usando obrigatoriamente uma pilha (com bits).
// Função : int emPilha(int num);
// ex: Decimal        14
// Em hexadecimal     0x0E
// em binário         00001110 (mostra na tela)
// Invertendo         01110000 (mostra na tela)
// Em hexadecimal     0x70
// Em decimal         112

#include <stdio.h>
#define BIT(I,N) I&(1<<N) // máscara para o enésemo bit de I

void printBinary(unsigned int x)
{
  for(int i=8*sizeof(x)-1; i>=0; i--)
    BIT(x,i) ? putchar('1') : putchar('0');
  printf("\n");
}

int emPilha(int num)
{
  int size = 8*sizeof(int); // tamanho da variável
  int stack = 0; // stack do mesmo tamanho da variável (apenas por opção);

  for (int i = size-1; i>=0; i--) // empilha
    if(BIT(num,i)) stack |= BIT((~0),((size-1) -i));

  // Poderia simplesmente retornar o stack, mas foi pedido para desempilhar.
  // Neste caso: trabalhando com um stack de bits do mesmo tamanho das
  // variáveis (int) seria melhor, ao invés de desempilhar bit-a-bit,
  // simplesmente retornar o stack.
  num = 0; // zera a variável;
  for(int i=8*size-1; i>=0; i--) // desempilha
    num |= BIT(stack,i);

  return num;
}

int main()
{
  int a = 0;

  printf("Entre com o inteiro a ser invertido e pressione <Enter>: ");
  scanf("%d", &a);
  getchar(); // limpa o buffer

  printf("Anterior à inversão:\n");
  printf("\tO binário (%lubits) de %010u é: ", 8*sizeof(a), a);
  printBinary(a);

  printf("Após a inversão:\n");

  a = emPilha(a);
  printf("\tO binário (%lubits) de %010u é: ", 8*sizeof(a), a);
  printBinary(a);

  return 0;
}
