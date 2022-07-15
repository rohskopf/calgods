#include<stdio.h>
#include<stdlib.h>

typedef struct tree{
  int item; // data item
  struct tree *parent; // pointer to parent
  struct tree *left; // pointer to left child
  struct tree *right; // pointer to right child
} tree;

void insert_tree(tree **l, int x, tree *parent){
  tree *p;

  if (*l == NULL){
    p = malloc(sizeof(tree));
    p->item = x;
    p->left = p->right = NULL;
    p->parent = parent;
    *l = p;
    return;
  }

  if (x< (*l)->item){
    insert_tree(&((*l)->left), x, *l);
  } else {
    insert_tree(&((*l)->right), x, *l);
  }

}

/*
In-order traversal.
Prints node values from left to right.
Why this works: Once you get to a NULL leaf, traverse_tree(l->left) will return,
then printf(l->item) runs, then the recursive chain traverse_tree(l->right)
starts. This can eventually go "upwards" by returning from the child calls.
Processing (printing) the item first yields a pre-order traversal.
Processing (printing) the item last gives a post-order traversal.
Each item is processed/printed once, so this has O(N) time where N = # nodes.
*/
void traverse_tree(tree *l) // displaying the nodes!
{
  if (l != NULL)
  {
    traverse_tree(l->left);
    printf("%d \n", l->item);
    traverse_tree(l->right);
  }
}

/*
Deleting a tree.
This is like traversing a tree, except we need to free each node instead of print.
We want to do post-order traversal since the order of this traversal is
left, right, root. That way we delete each child node.
*/
void delete_tree(tree *l) // displaying the nodes!
{
  if (l != NULL)
  {
    delete_tree(l->left);
    delete_tree(l->right);
    free(l);
  }
}

/*
Searching a tree.
This search algorithm runs in O(h) time, where h is height of tree.
*/
tree *search_tree(tree *l, int x){

  if (l == NULL){
    return(NULL);
  }

  if (l->item == x){
    return(l);
  }

  if (x < l->item){
    return(search_tree(l->left, x));
  } else {
    return(search_tree(l->right, x));
  }

}

int main(){

  printf("Binary Tree in C\n\n");

  tree *root_node = NULL;

  insert_tree(&root_node, 10, NULL);
  insert_tree(&root_node, 20, NULL);
  insert_tree(&root_node, 30, NULL);
  insert_tree(&root_node, 5, NULL);

  // try printing parts of this linked list to get familiar with how it's organized

  //printf("%d\n", root_node->item);
  //printf("%d\n", root_node[1].item);

  // traverse the tree

  printf("In-order traversal:\n");
  traverse_tree(root_node);

  // search the tree for a value

  tree *searched = search_tree(root_node, 20);
  if (searched != NULL){
    printf("Searched value: %d\n", searched->item);
  } else {
    printf("Value not found.\n");
  }

  // delete the tree

  delete_tree(root_node);


  return 0;
}
