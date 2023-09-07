#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define QUEUE_EMPTY INT_MIN

typedef struct {
  int *values;
  int head, tail, num_entries, size;
} queue;

void init_queue(queue *q, int max_size) {
  q->values = malloc(sizeof(int) * max_size);
  q->size = max_size;
  q->num_entries = 0;
  q->head = 0;
  q->tail = 0;
}

bool queue_empty(queue *q) {
  return (q->num_entries == 0);
}

bool queue_full(queue *q) {
  return (q->num_entries == q->size);
}

void queue_destory(queue *q) {
  free(q->values);
}

bool enqueue(queue *q, int value) {
  if (queue_full(q)) {
    return false;
  }
  q->values[q->tail] = value;
  q->num_entries++;
  q->tail = (q->tail + 1) % q->size;
  return true;
}

int dequeue(queue *q) {
  if (queue_empty(q)) {
    return QUEUE_EMPTY;
  }
  int result;
  result = q->values[q->head];
  q->head = (q->head + 1) % q->size;
  q->num_entries--;
  return result;
}

int main() {
  queue q;
  init_queue(&q, 5);
  enqueue(&q, 1);
  enqueue(&q, 2);
  enqueue(&q, 3);
  enqueue(&q, 4);
  enqueue(&q, 5);
  enqueue(&q, 6);
  int t;
  while ((t = dequeue(&q)) != QUEUE_EMPTY) {
    printf("%d\n", t);
  }
  queue_destory(&q);
  return 0;
}
