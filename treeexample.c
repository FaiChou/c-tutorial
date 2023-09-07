#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

typedef struct treenode {
  int value;
  struct treenode *left;
  struct treenode *right;
} treenode;

treenode *createnode(int value) {
  treenode *node = malloc(sizeof(treenode));
  if (node != NULL) {
    node->value = value;
    node->left = NULL;
    node->right = NULL;
  }
  return node;
}

void printtabs(int numtabs) {
  for (int i=0; i < numtabs; ++i) {
    printf("\t");
  }
}

void printtree_rec(treenode *root, int level) {
  if (root == NULL) {
    printtabs(level);
    printf("---<empty>---\n");
    return;
  }
  printtabs(level);
  printf("value = %d\n", root->value);
  printtabs(level);
  printf("left\n");
  
  printtree_rec(root->left, level+1);
  printtabs(level);
  printf("right\n");
  
  printtree_rec(root->right, level+1);

  printtabs(level);
  printf("done\n");
}

void printtree(treenode *root) {
  printtree_rec(root, 0);
}

bool insertnumber(treenode **rootptr, int value) {
  treenode *root = *rootptr;
  if (root == NULL) {
    // tree is empty
    *rootptr = createnode(value);
    return true;
  }
  if (value == root->value) {
    return false;
  }
  if (value < root->value) {
    return insertnumber(&(root->left), value);
  } else {
    return insertnumber(&(root->right), value);
  }
}

bool findnumber(treenode *root, int value) {
  if (root == NULL) return false;
  if (root->value == value) {
    return true;
  }
  if (value < root->value) {
    return findnumber(root->left, value);
  } else {
    return findnumber(root->right, value);
  }
}

int main() {
  treenode *root = NULL;
  
  insertnumber(&root, 15);
  insertnumber(&root, 11);
  insertnumber(&root, 24);
  insertnumber(&root, 5);
  insertnumber(&root, 19);
  insertnumber(&root, 16);
  printtree(root);

  printf("%d (%d)\n", 16, findnumber(root, 16));
  printf("%d (%d)\n", 15, findnumber(root, 15));
  printf("%d (%d)\n", 5, findnumber(root, 5));
  printf("%d (%d)\n", 1, findnumber(root, 1));
  printf("%d (%d)\n", 7, findnumber(root, 7));
  return 0;
}
