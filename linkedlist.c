#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
  int value;
  struct node *next;
  struct node *prev;
};

typedef struct node node_t;

void printlist(node_t *head) {
  node_t *temp = head;
  while (temp != NULL) {
    printf("%d ", temp->value);
    temp = temp->next;
  }
  printf("\n");
}

node_t *create_new_node(int value) {
  node_t *n = malloc(sizeof(node_t));
  n->value = value;
  n->next = NULL;
  n->prev = NULL;
  return n;
}

node_t *insert_at_head(node_t **head, node_t *node_to_insert) {
  node_to_insert->next = *head;
  if (*head != NULL) {
    (*head)->prev = node_to_insert;
  }
  *head = node_to_insert;
  node_to_insert->prev = NULL;
  return node_to_insert;
}

node_t *find_node(node_t *head, int value) {
  while (head != NULL) {
    if (head->value == value) return head;
    head = head->next;
  }
  return NULL;
}

void insert_after_node(node_t *node_to_insert_after, node_t *newnode) {
  newnode->next = node_to_insert_after->next;
  if (newnode->next != NULL) {
    newnode->next->prev = newnode;
  }
  newnode->prev = node_to_insert_after;
  node_to_insert_after->next = newnode;
}

void free_all_nodes(node_t **head) {
  while (*head != NULL) {
    node_t *temp = *head;
    *head = (*head)->next;
    free(temp);
  }
  *head = NULL;
}

void remove_node(node_t **head, node_t *node_to_remove) {
  if (*head == node_to_remove) {
    *head = node_to_remove->next;
    if (*head != NULL) {
      (*head)->prev = NULL;
    }
  } else {
    node_to_remove->prev->next = node_to_remove->next;
    if (node_to_remove->next != NULL) {
      node_to_remove->next->prev = node_to_remove->prev;
    }
  }
  node_to_remove->next = NULL;
  node_to_remove->prev = NULL;
  // free(node_to_remove); // don't free it, bcz can not sure it was created in the heap
}

int main() {
  node_t *head = NULL;
  node_t *temp;
  for (int i = 25; i > 0; --i) {
    temp = create_new_node(i);
    insert_at_head(&head, temp);
  }

  temp = find_node(head, 13);
  if (temp != NULL) {
    printf("found node with value: %d\n", temp->value);
    insert_after_node(temp, create_new_node(100));
  }
  printlist(head);
  temp = find_node(head, 100);
  remove_node(&head, temp->next);
  printlist(head);
  free_all_nodes(&head);
  printlist(head);
  return 0;
}
