#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define STACK_LENGTH 5
#define EMPTY (-1)
#define STACK_EMPTY INT_MIN

typedef struct node {
  int value;
  struct node *next;
} node;

typedef node * stack;

bool push(stack *mystack, int value) {
  node *newnode = malloc(sizeof(node));
  if (newnode == NULL) return false;
  newnode->next = *mystack;
  newnode->value = value;
  *mystack = newnode;
  return true;
}

int pop(stack *mystack) {
  if (*mystack == NULL) return STACK_EMPTY;
  int value = (*mystack)->value;
  node *tmp = *mystack;
  *mystack = (*mystack)->next;
  free(tmp);
  return value;
}

int main() {
  stack s1 = NULL, s2 = NULL, s3 = NULL;
  push(&s2, 1);
  push(&s2, 2);
  push(&s2, 3);
  int t;
  while ((t = pop(&s2)) != STACK_EMPTY) {
    printf("%d\n", t);
  }
  return 0;
}