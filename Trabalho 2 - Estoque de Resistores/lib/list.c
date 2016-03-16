#include "list.h"

void checkMalloc(void* ptr)
{
	if(!ptr){
		printf("Memória cheia. O programa será encerrado. \n");
		getchar();
		exit(EXIT_FAILURE);
	}
}

// FIXME!
list_t *binSearchList(lheader_t *mlH, float value)
{
	if(mlH){
		unsigned int n, a = 0, b = (*mlH).size;
		list_t *mlist;
		for(n=b/2;(a!=b-1);n=(b+a)/2){
			// printf("value=%d ? %d v[%d], a=%d, b=%d \n", value, (*mlist).value, n+1, a, b); //debug
			mlist = (*mlH).start;
			for(int i=0;i<n;i++) mlist = (*mlist).next;
			if((*mlist).value == value) return mlist; //encontrado
			else if((*mlist).value<value) a=n;
			else b=n;
		}
	}
	return NULL; //nao encontrado
}

list_t *searchList(lheader_t *mlH, float value)
{
	int i;
	list_t *mlist = (*mlH).start;
	for(i=0;i<(*mlH).size;i++)
		if((*mlist).value == value) return mlist;
		else mlist = (*mlist).next;
	return NULL;
}


list_t *searchChild(lheader_t *mlH, float value)
{
	if(mlH){
		list_t *mlist = (*mlH).start;
		for(int i = (*mlH).size; i > 0; i--){
			if((*(list_t*)(*mlist).child).value == value) return (*mlist).child;
			else mlist = (*mlist).next;
		}
	}
	return NULL; //nao encontrado
}

list_t *insertList(lheader_t *mlH, float i, void *child)
{
	if(!mlH) return NULL;
	list_t *novo = NULL; // cria novo item
	
	printf("\n\t\t\t\t (NEW LIST)~>(mlH)%p, (val)%.2f, (child)%p", mlH, i, child); getchar();
	
	// caso inicial, quando a lista foi inicializada com nulo
	if(!(*(*mlH).start).value){
		(*(*mlH).start).value = i;
		(*(*mlH).start).next = (*(*mlH).start).fore = NULL;
		novo = (*mlH).start;
	}else{
		// define o novo item
		novo = (list_t*)malloc(sizeof(list_t));
		(*novo).next = (*novo).fore = NULL;
		(*novo).value = i;
		(*novo).child = child;

		list_t *p = (*mlH).start; // ponteiro que percorre a lista
		if( (*novo).value < (*(*mlH).start).value ){
			// Insere no início
      (*novo).next = (*mlH).start;
			(*(*mlH).start).fore = novo;
			(*mlH).start = novo;
      (*mlH).size++;
    }else for(p = (*mlH).start; ; p = (*p).next){ // Percorre a lista.
			// if((*novo).value == (*p).value){ 	// Caso o item já exista
			// 	return p;  												// retona um ptr para ele.
			// }else 
			if( (!(*p).next) || ((*(*p).next).value > (*novo).value) ){
				// insere no meio ou no fim
				(*novo).next = (*p).next;
				(*novo).fore = p;
				if((*p).next) (*(*p).next).fore = novo;
				(*p).next = novo;
				(*mlH).size++;
				break;
      }
    }
	}

	return novo; // retorna o novo item
}

lheader_t *createList()
{
	// Cria lista
	list_t *mlist = (list_t*)calloc(1, sizeof(list_t));

	// Cria cabecalho e associa à lista
	lheader_t *mlH = (lheader_t*)malloc(sizeof(lheader_t));
	(*mlH).size = 1;
	(*mlH).start = (*mlH).end = mlist;

	return mlH;
}

void freeList(lheader_t *mlH)
{
	list_t *mlist = (*mlH).start;
	for (int i=0;i<(*mlH).size-1;i++){
		free(mlist);
		mlist = (*mlist).next;
	}
	free(mlH);
	mlH = NULL;
}

void printList(lheader_t *mlH)
{
	list_t *mlist = (*mlH).start;
	for(int i=0; i<(*mlH).size; i++){
		printf("%.2f\t", (*mlist).value);
		mlist = (*mlist).next;
	}
	printf("\n");
}

void swapPointer(list_t *l1, list_t *l2)
{
	int tmp = (*l1).value;
	(*l1).value = (*l2).value;
	(*l2).value = tmp;
}

void sortList(lheader_t* mlH)
{
	list_t *mlist = (*mlH).start;

	while(mlist!=NULL){
		int temp = (*mlist).value;
		list_t *nlist = (*mlH).start;
		while((nlist!=mlist)){
			if((*nlist).value > temp){
				(*mlist).value = (*nlist).value;
				(*nlist).value = temp;
				temp = (*mlist).value;
			}
			nlist = (*nlist).next;
		}
		mlist = (*mlist).next;
	}
}

int removeList(lheader_t *mlH, list_t *mlist)
{
	if (!mlist){
		return -1; //erro
	}else{
		list_t *elemento_fore = (*mlist).fore;
		list_t *elemento_next = (*mlist).next;

		if(mlist == (*mlH).start){
			(*mlH).start = (*mlist).next;
			(*elemento_next).fore = NULL;
		}else if(mlist == (*mlH).end){
			(*mlH).end = (*mlist).fore;
			(*elemento_fore).next = NULL;
		}else{
			(*elemento_fore).next = (*mlist).next;
			(*elemento_next).fore = (*mlist).fore;
		}

		(*mlH).size-=1;
		free(mlist);

		return 0; //ok
	}
}

