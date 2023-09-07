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

node *head = NULL;

bool push(int value) {
  node *newnode = malloc(sizeof(node));
  if (newnode == NULL) return false;
  newnode->next = head;
  newnode->value = value;
  head = newnode;
  return true;
}

int pop() {
  if (head == NULL) return STACK_EMPTY;
  int value = head->value;
  node *tmp = head;
  head = head->next;
  free(tmp);
  return value;
}

int main() {
  push(1);
  push(2);
  push(3);
  int t;
  while ((t = pop()) != STACK_EMPTY) {
    printf("%d\n", t);
  }
  return 0;
}