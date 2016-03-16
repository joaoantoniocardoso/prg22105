#ifndef __list_h
#define __list_h

#include <stdio.h>
#include <stdlib.h>

#include "menu.h" //onde estão as funções que integram o menu
#include "data.h" //onde a struct é definida
// #include "list.h" //a biblioteca para listas duplamente encadiadas heterogeneas
#include "file.h" //onde estão as funções que trabalham com arquivos
#include "tree.h" //onde estão as funções que trabalham com árvores
#include "typedef.h" //onde os typedefs estão definidos

// estruturas da lista
struct list{
	float value;
	void *child;
	struct list *fore;
	struct list *next;
};

struct listHeader{
	int size;
	list_t *start;
	list_t *end;
};

/**
 * Checks for some memory allocation error.
 * @method checkMalloc
 * @param  ptr         Ptr to a var allocated.
 */
void checkMalloc(void *ptr);

/**
 * Insert values in a sorted way.
 * @method insertSortedList
 * @param  mlH              Header of the list.
 * @param  i                Integet to insert.
 * @param  child            [description]
 * @return                  Ptr to added item.
 */
list_t *insertList(lheader_t *mlH, float i, void *child); // FIXME!

/**
 * Creates an empty list.
 * @method createList
 * @return               Header of the list.
 */
lheader_t *createList();

/**
 * Recursively free the entire list.
 * @method freeList
 * @param  mlH      Header of the list.
 */
void freeList(lheader_t *mlH);

/**
 * Print the entire list
 * @method printList
 * @param  mlH          Header of the list
 */
void printList(lheader_t *mlH);

/**
 * Swap data between two lists.
 * @method swapPointer
 * @param  elemento1   list 1
 * @param  elemento2   list 2
 */
void swapPointer(list_t *l1, list_t *l2);

/**
 * Sort the list using insertion algorithm
 * @method insertionSortList
 * @param  mlH                  Header of the list
 */
void sortList(lheader_t* mlH);

/**
 * Binary search on the list.
 * @method binarySearchList
 * @param  mlH                 Header of the list.
 * @param  value               Value to be looked.
 * @return                     Ptr to the found, otherwise NULL.
 */
list_t *binSearchList(lheader_t *mlH, float value);

/**
 * Search for a value in the list
 * @method searchList
 * @param  mlH                 Header of the list.
 * @param  value               Value to be looked.
 * @return                     Ptr to the found, otherwise NULL.
 */
list_t *searchList(lheader_t *mlH, float value);

/**
 * Search for a specific child of a list
 * @method searchChild
 * @param  mlH                 Header of the list.
 * @param  value               Value to be looked.
 * @return                     Ptr to father of the found, otherwise NULL.
 */
void *searchChild(lheader_t *mlH, float value);

/**
 * Remove an item from list.
 * @method removeList
 * @param  mlH           [description]
 * @param  mlist         Element to be removed.
 * @return               0 its ok, otherwise error.
 */
int removeList(lheader_t *mlH, list_t *mlist);

#endif