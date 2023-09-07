#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define STACK_LENGTH 5
#define EMPTY (-1)
#define STACK_EMPTY INT_MIN

typedef struct {
  int values[STACK_LENGTH];
  int top;
} stack;

bool push(stack *mystack, int value) {
  if (mystack->top >= STACK_LENGTH - 1) return false;
  mystack->top++;
  mystack->values[mystack->top] = value;
  return true;
}

int pop(stack *mystack) {
  if (mystack->top == EMPTY) return STACK_EMPTY;
  int value = mystack->values[mystack->top];
  mystack->top--;
  return value;
}

int main() {
  stack s1;
  s1.top = EMPTY;
  stack s2;
  s2.top = EMPTY;
  stack s3;
  s3.top = EMPTY;
  push(&s2, 1);
  push(&s2, 2);
  push(&s2, 3);
  int t;
  while ((t = pop(&s2)) != STACK_EMPTY) {
    printf("%d\n", t);
  }
  return 0;
}