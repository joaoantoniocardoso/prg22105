#include "tree.h"

int float_is_lass_than(float f1, float f2){
  // se f1 < f2
  return ((int)(f1*100000)) < ((int)(f2*100000));
}

node_t *insertTree(node_t *node, float val, float qtd)
{
  if(node == NULL){ // Cria a árvore caso for nula
    node_t *temp =  (node_t *)malloc(sizeof(node_t));
    (*temp).left = (*temp).right = NULL;
    (*temp).val = val;
    (*temp).qtd = qtd;
    printf("\t\t\t\t (NEW NODE)~> %f, %f\n", val, qtd);
    return temp;
  }
  printf("\t\t\t\t\t\t\t\tval:%d < %d = %d\n",((int)(val*100000.f)), ((int)((*node).val*100000.f)), ((int)(val*100000)) < ((int)((*node).val*100000)) );
  if(float_is_lass_than(val, (*node).val) )
    (*node).left  = insertTree((*node).left, val, qtd);
  else if(!float_is_lass_than(val, (*node).val))
    (*node).right = insertTree((*node).right, val, qtd);   

  return node;
}

void freeTree(node_t * tree)
{
  if (tree){
    freeTree(tree->left);
    freeTree(tree->right);
    free(tree);
  }
}

void printTree(node_t *tree)
{
	if (tree) printf("<%.2f",(*tree).val);
	else printf("<>");
	if ((*tree).left) printTree((*tree).left);
	else printf("<>");
	if ((*tree).right) printTree((*tree).right);
	else printf("<>");
	printf(">");
}

node_t *searchTree(node_t *tree, float val)
{
  if(!tree) return NULL;
  else if(val == (*tree).val) return tree;
  else if(val < (*tree).val) return searchTree((*tree).left, val);
  else return searchTree((*tree).right, val);
}