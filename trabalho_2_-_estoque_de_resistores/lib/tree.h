#ifndef __tree_h
#define __tree_h

#include<stdlib.h>
#include<stdio.h>

#include "menu.h" //onde estão as funções que integram o menu
#include "data.h" //onde a struct é definida
#include "list.h" //a biblioteca para listas duplamente encadiadas heterogeneas
#include "file.h" //onde estão as funções que trabalham com arquivos
// #include "tree.h" //onde estão as funções que trabalham com árvores
#include "typedef.h" //onde os typedefs estão definidos

struct btree{
  float val, qtd;
  struct btree *right, *left;
};

/**
 * Insert node in a binary sorted tree
 * @method insertTree
 * @param  node          The tree's root where it is suposed to be inserted,
 *                       but when NULL it forces a new tree to be created.
 * @param  val           Ohmic value of resistence.
 * @param  qtd           In stock quantity of the resistor.
 * @return               The new root's tree (new or updated).
 */
node_t *insertTree(node_t *node, float val, float qtd);

/**
 * Recursively free the tree.
 * @method freeTree
 * @param  tree     The root of the tree.
 */
void freeTree(node_t * tree);

/**
 * Prints the binary tree in travessal mode.
 * @method printTree
 * @param  tree      The root of the tree.
 */
void printTree(node_t *tree);

/**
 * Search in the binary tree
 * @method searchTree
 * @param  tree       Root of the tree.
 * @param  i          Value to be searched.
 * @return            Return the found, otherwise NULL.
 */
node_t *searchTree(node_t *tree, float val);

#endif