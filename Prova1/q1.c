// Questão 1:
// Implemente em C um programa para manipular um buffer de caracteres formado
// por uma fila circular com seguintes funções:
// Cria um buffer com tamanho definido pelo usuário.
// struct buffer *cria(int size)
// Limpa o buffer. Obs.: Não libera apenas esvazia o mesmo.
// int limpa(struct buffer *)
// Apaga o buffer.
// int apaga(struct buffer *)
// Lê um determinado número (tam) de caracteres do buffer e retorna pela
// referencia "ret". Apaga os caracteres lidos. Caso o número de dados menor
// que tam retorna a quantidade existente "return". Caso buffer vazio
// retorna -1.
// int lebuffer(char *ret, int tam, struct buffer *list)

// Nota1: a única aplicação onde vejo vantagem utilizar um buffer circular
// implementado com listas é quando o tamanho do buffer pode ser variável. Em
// todos os outros casos vejo claramente que uma implementação por vetores
// seria muito mais eficiente (necessita menos memória e é mais ágil).

// Nota2: optei por utilizar um cabeçalho para a lista: apenas alguns bytes a
// mais que reduzem bastante a complexidade de algumas funções.

#include <stdlib.h>
#include <stdio.h>

// Cabeçalho do buffer circular
struct buffer
{ 
  struct ring *newest;
  struct ring *oldest;
  unsigned int size;
  unsigned int q;
};

// Nó do buffer circular
struct ring
{ 
  struct ring *newer;
  char data;
};

// Brusco tratamento para falta de memória durante alocação dinâmica
void erralloc()
{
	printf("Error: insufficient memory.\n");
	exit(EXIT_FAILURE);
}

// Cria um buffer com tamanho definido pelo usuário.
struct buffer *cria(int size)
{
  // aloca o último
  struct ring *lastRing = (struct ring*)malloc(sizeof(struct ring));
  if(!lastRing) erralloc();
  
  // aloca o restante
  struct ring *nring = lastRing;
  for(int i = 1; i < size; i++){
    struct ring *mring = (struct ring*)malloc(sizeof(struct ring));
    if(!mring) erralloc();
    (*mring).newer = nring;
    nring = mring;
  }
  (*lastRing).newer = nring; // o ultimo aponta para o primeiro
  
  // aloca e atualiza o header
  struct buffer *mbuffer = (struct buffer*)malloc(size*sizeof(struct buffer));
  if(!mbuffer) erralloc();
  (*mbuffer).newest = (*mbuffer).oldest = lastRing;
  (*mbuffer).size = size;
  (*mbuffer).q = 0;
  
  return mbuffer;
}

// Insere itens no buffer.
void escreveBuffer(char c, struct buffer *mbuffer)
{
  if((*mbuffer).q >= (*mbuffer).size) return; // quando buffer está cheio
  if((*mbuffer).q) // quando o buffer não está vazio
    (*mbuffer).newest = (*(*mbuffer).newest).newer; // atualiza o cabeçalho
  (*mbuffer).q++;

  (*(*mbuffer).newest).data = c; // insere o dado na posição mais antiga
  printf("'%c',", (*(*mbuffer).newest).data);                  // debug
}

// Limpa o buffer. Obs.: Não libera apenas esvazia o mesmo.
int limpa(struct buffer *mbuffer)
{
  (*mbuffer).newest = (*mbuffer).oldest;
  (*mbuffer).q = 0;
  return 0;
}

// Apaga o buffer.
int apaga(struct buffer *mbuffer)
{
  struct ring *nring, *mring = (*mbuffer).newest;
  
  for(int i = (*mbuffer).size; i>0; i--){
		nring = (*mring).newer;
		free(mring);
    mring = nring;
	}
  free(mbuffer);
  return 0;
};

// Lê um determinado número (tam) de caracteres do buffer e retorna pela
// referencia "ret". Apaga os caracteres lidos. Caso o número de dados menor
// que tam retorna a quantidade existente "return". Caso buffer vazio
// retorna -1.
int lebuffer(char *ret, int tam, struct buffer *mbuffer)
{
  if(!(*mbuffer).q) return -1; // quando buffer vazio
  if(tam > (*mbuffer).q) tam = (*mbuffer).q; // limita o tamanho a ser lido
  
  struct ring *mring = (*mbuffer).oldest; // guarda a referencia do mais antigo
  int i = 0;
  for(; i < tam; mring = (*mring).newer, i++)
    ret[i] = (*mring).data; // transfere os dados
  ret[i] = '\0'; // delimita o fim da string
  
  // atualiza o cabeçalho:
  (*mbuffer).q -= i;
  (*mbuffer).oldest = mring;
  
  printf("out<\t\t'%s'\n", ret);                                       // debug
  
  return (*mbuffer).q; // retorna o tamanho do buffer
}

// Imprime o buffer
void printBuffer(struct buffer *mbuffer)
{
  if((*mbuffer).q==0) printf("<buffer vazio>");                  // debug
  struct ring *mring = (*mbuffer).oldest;
  for(int i = (*mbuffer).q; i > 0; mring = (*mring).newer, i--)
    printf("'%c',", (*mring).data);
  putchar('\n');
}

int main(){
  // cria o buffer
  struct buffer *mbuffer = cria(16);
  
  printf("A rotina a seguir testará o estouro e esvaziamento de um buffer \n\
  circular hora com fluxo de entrada maior que a saída, hora o contrário.\n");
  for(int j = 0; j<5; j++){
  
    // O programa escreve no buffer
    printf("in>\t\t");
    for(int i = 0; i < 12; i++) escreveBuffer(i+97, mbuffer);    
    putchar('\n');
    
    // imprime o buffer
    printf("Buff(%02d/%02d):\t", (*mbuffer).q, (*mbuffer).size);
    printBuffer(mbuffer);
    
    // E o programa lê do buffer, porém mantendo o fluxo menor que a escrita,
    // para causar um estouro no buffer.
    char bufferlido1[8];
    if(lebuffer(bufferlido1, 6, mbuffer)==0)
      printf("lido:\t\t'%s'\n", bufferlido1);
      
    // imprime o buffer
    printf("Buff(%02d/%02d):\t", (*mbuffer).q, (*mbuffer).size);
    printBuffer(mbuffer);
  
    // Depois de algumas repetições digamos que o o fluxo de saída melhore e
    // deste modo ele consiga esvaziar todo o buffer rapidamente.
    if(j>2){
      char bufferlido2[20];
      if(lebuffer(bufferlido2, 20, mbuffer)==0)
      printf("lido:\t\t'%s'\n", bufferlido2);
      
      // imprime o buffer
      printf("Buff(%02d/%02d):\t", (*mbuffer).q, (*mbuffer).size);
      printBuffer(mbuffer);
    }  
  }
  
  apaga(mbuffer); // libera o buffer
  
  printf("\nFim de teste.\n");
  
  return 0;
}