#include "lista-duplamente-encadiada-heterogenea.h"

struct lista *criar_itemlista(void* dado_inicial){
	//cria itemlista
	struct itemlista *mitemlista = (struct itemlista*)malloc(sizeof(struct itemlista));

	//atribui dado inicial
	(*mitemlista).dado = dado_inicial;

	//anula ponteiros pois é o único elemento
	(*mitemlista).proximo = NULL;
	(*mitemlista).anterior = NULL;

	// //cria cabecalho
	struct lista *mlista = (struct lista*)malloc(sizeof(struct lista));
	(*mlista).size = 1;
	(*mlista).start = mitemlista;
	(*mlista).end = mitemlista;

	return mlista;
}

//insere um elemento no final da itemlista
struct itemlista *inserir_elemento_final(struct lista *mitemlista, void* dado_inicial){
	struct itemlista *novo_elemento = (struct itemlista*)malloc(sizeof(struct itemlista));
	struct itemlista *ultimo_antigo = (*mitemlista).end;

	//reaponta
	(*ultimo_antigo).proximo = novo_elemento;
	(*novo_elemento).anterior = (*mitemlista).end;
	(*mitemlista).end = novo_elemento;
	(*mitemlista).size++;

	//atribui dado inicial
	(*novo_elemento).dado = dado_inicial;

	return novo_elemento;
}
//todo: char run_all_list para percorrer a lista inteira ou retornar no primeiro caso de retorno de ponteiro não nulo
void *percorre_lista(struct lista *mlista, void *(*functionPtr)(void *dado, int n, va_list vargs), int n, ...){
	struct itemlista *mitemlista = (*mlista).start;
	int j;
	va_list args;
	void *r1 = NULL, *r2 = NULL;

	//percorre a lista
	for (j = 0; j < (*mlista).size ; j++){
		va_start(args, n); //recebe os argumentos da va_list args
		r1 = (*functionPtr)( (*mitemlista).dado, n, args);
		if (r1!=NULL) r2 = r1;
		mitemlista = (*mitemlista).proximo;
		va_end(args); //limpa a lista
	}

	//retorna
	return r2;
}

struct itemlista *___compara_elemento_com_dado(struct lista *mlista, void *dado){
	struct itemlista *mitemlista = (*mlista).start;
	int j;

	for (j = 0; j < (*mlista).size ; j++){
		if((*mitemlista).dado == dado) return mitemlista;;
		mitemlista = (*mitemlista).proximo;
	}
	return NULL;
}

void *remover_elemento(struct lista *mlista, void *dado){
	if (dado==NULL) return NULL; //erro
	else{

		struct itemlista *elemento = ___compara_elemento_com_dado(mlista, dado);
		struct itemlista *elemento_anterior = (*elemento).anterior;
		struct itemlista *elemento_proximo = (*elemento).proximo;
		
		if((*elemento).proximo == NULL){
			//ultimo
			(*mlista).end = (*elemento).anterior;
			(*elemento_anterior).proximo = NULL;

		}else if((*elemento).anterior == NULL){
			//primeiro
			(*mlista).start = (*elemento).proximo;
			(*elemento_proximo).anterior = NULL;
		}else{
			(*elemento_anterior).proximo = (*elemento).proximo;
			(*elemento_proximo).anterior = (*elemento).anterior;
		}

		(*mlista).size--;
		// free((*elemento).dado);
		free(elemento);

		return &((*elemento).dado); //ok
	}
}