#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define QUEUE_EMPTY INT_MIN

typedef struct node {
  int value;
  struct node *next;
} node;

typedef struct {
  node *head;
  node *tail;
} queue;

void init_queue(queue *q) {
  q->head = NULL;
  q->tail = NULL;
}

bool enqueue(queue *q, int value) {
  node *newnode = malloc(sizeof(node));
  if (newnode == NULL) return false;
  newnode->value = value;
  newnode->next = NULL;
  if (q->tail != NULL) {
    q->tail->next = newnode;
  }
  q->tail = newnode;
  if (q->head == NULL) {
    q->head = newnode;
  }
  return true;
}

int dequeue(queue *q) {
  if (q->head == NULL) return QUEUE_EMPTY;
  node *tmp = q->head;
  int result = tmp->value;
  q->head = q->head->next;
  if (q->head == NULL) {
    q->tail = NULL;
  }
  free(tmp);
  return result;
}

int main() {
  queue q1, q2, q3;
  init_queue(&q1);
  init_queue(&q2);
  init_queue(&q3);
  enqueue(&q2, 1);
  enqueue(&q2, 2);
  enqueue(&q2, 3);
  int t;
  while ((t = dequeue(&q2)) != QUEUE_EMPTY) {
    printf("%d\n", t);
  }
  return 0;
}
