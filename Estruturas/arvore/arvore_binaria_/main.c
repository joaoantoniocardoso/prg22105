#include<stdlib.h>
#include<stdio.h>

struct btree{
  int data;
  struct btree *right, *left;
};
typedef struct btree node_t;

void insert(node_t ** tree, int i)
{
  node_t *temp = NULL;
  if(!(*tree))
  {
    temp = (node_t *)malloc(sizeof(node_t));
    temp->left = temp->right = NULL;
    temp->data = i;
    *tree = temp;
    return;
  }

  if(i < (*tree)->data)
  {
    insert(&(*tree)->left, i);
  }
  else if(i > (*tree)->data)
  {
    insert(&(*tree)->right, i);
  }

}

void print_preorder(node_t * tree)
{
  if (tree)
  {
    printf("%d\n",tree->data);
    print_preorder(tree->left);
    print_preorder(tree->right);
  }

}

void print_inorder(node_t * tree)
{
  if (tree)
  {
    print_inorder(tree->left);
    printf("%d\n",tree->data);
    print_inorder(tree->right);
  }
}

void print_postorder(node_t * tree)
{
  if (tree)
  {
    print_postorder(tree->left);
    print_postorder(tree->right);
    printf("%d\n",tree->data);
  }
}

void deltree(node_t * tree)
{
  if (tree)
  {
    deltree(tree->left);
    deltree(tree->right);
    free(tree);
  }
}

// imprime a árvore (travessal mode)
void printTree(node_t *tree)
{
	if (tree!=NULL) printf("<%d",(*tree).data);
	else printf("<>");
	if ((*tree).left!=NULL) printTree((*tree).left);
	else printf("<>");
	if ((*tree).right!=NULL) printTree((*tree).right);
	else printf("<>");
	printf(">");
}

node_t* search(node_t *tree, int i)
{
  if(!tree) return NULL;
  else if(i == (*tree).data) return tree;
  else if(i < (*tree).data) return search((*tree).left, i);
  else return search((*tree).right, i);
}

int main()
{
  node_t *root;
  node_t *tmp;
  //int i;

  root = NULL;
  /* Inserting nodes into tree */
  insert(&root, 1);
  insert(&root, 2);
  insert(&root, 3);
  insert(&root, 4);
  insert(&root, 5);
  insert(&root, 6);
  insert(&root, 7);

  printf("Travessal Pre Order Display\n");
  printTree(root);
  putchar('\n');

  /* Search node into tree */
  tmp = search(root, 2);
  if (tmp)
  {
    printf("Searched node=%d\n", tmp->data);
  }
  else
  {
    printf("Data Not found in tree.\n");
  }

  /* Deleting all nodes of tree */
  deltree(root);
  
  return 0;
}
