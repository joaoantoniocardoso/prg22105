#ifndef __lista_duplamente_encadiada_heterogenea
#define __lista_duplamente_encadiada_heterogenea

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

struct itemlista{
	void *dado;
	struct itemlista *anterior;
	struct itemlista *proximo;
};

struct lista{
	int size;
	struct itemlista *start;
	struct itemlista *end;
};

struct lista *criar_lista(void* dado_inicial);

//cria lista com um item com dado_inicial
struct lista *criar_itemlista(void* dado_inicial);

//insere um elemento no final da itemlista
struct itemlista *inserir_elemento_final(struct lista *mlista, void* dado_inicial);

//executa a função functionPtr passada pelo usuário aplicando a lista de argumentos variaveis na functionPtr e retorna o retorno da função functionPtr
void *percorre_lista(struct lista *mlista, void *(*functionPtr)(void *dado, int n, va_list vargs), int n, ...);

//retorna ponteiro para o dado removido
void *remover_elemento(struct lista *mlista, void *dado);

#endif