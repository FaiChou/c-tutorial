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
  if (n == NULL) {
    printf("Error: Failed to allocate memory for new node\n");
    return NULL;
  }
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

node_t *find_node(node_t *n, int value) {
  while (n != NULL) {
    if (n->value == value) return n;
    n = n->next;
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

node_t *remove_node(node_t **head, node_t *node_to_remove) {
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
  return node_to_remove;
}

int main() {
  node_t *head = NULL;
  node_t *temp;
  for (int i = 25; i > 0; --i) {
    temp = create_new_node(i);
    if (temp == NULL) {
      printf("Error: Failed to create new node\n");
      return 1;
    }
    insert_at_head(&head, temp);
  }

  temp = find_node(head, 13);
  if (temp != NULL) {
    printf("found node with value: %d\n", temp->value);
    node_t *new_node = create_new_node(100);
    if (new_node == NULL) {
      printf("Error: Failed to create new node\n");
      return 1;
    }
    insert_after_node(temp, new_node);
  }
  printlist(head);
  temp = find_node(head, 100);
  node_t *removed = remove_node(&head, temp->next);
  printf("removed node with value: %d\n", removed->value);
  free(removed);
  printlist(head);
  free_all_nodes(&head);
  printlist(head);
  return 0;
}
