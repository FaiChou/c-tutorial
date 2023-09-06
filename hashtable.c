#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_NAME 256
#define TABLE_SIZE 10

typedef struct {
  char name[MAX_NAME];
  int age;
} person;

person *hash_table[TABLE_SIZE];

unsigned int hash(char *name) {
  int l = strnlen(name, MAX_NAME);
  unsigned int hash_value = 0;
  for (int i = 0; i < l; ++i) {
    hash_value += name[i];
    hash_value = (hash_value * name[i]) % TABLE_SIZE;
  }
  return hash_value;
}

void print_table() {
  printf("Start\n");
  for (int i = 0; i < TABLE_SIZE; ++i) {
    if (hash_table[i] == NULL) {
      printf("\t%i\t---\n", i);
    } else {
      printf("\t%i\t%s\n", i, hash_table[i]->name);
    }
  }
  printf("End\n");
}

void init_hash_table() {
  for (int i = 0; i < TABLE_SIZE; i++) {
    hash_table[i] = NULL;
  }
}

bool hash_table_insert(person *p) {
  if (p == NULL) return false;
  int index = hash(p->name);
  // printf("%d\n", index);
  if (hash_table[index] != NULL) return false;
  hash_table[index] = p;
  return true;
}

person *hash_table_lookup(char *name) {
  int index = hash(name);
  if (hash_table[index] != NULL &&
    strncmp(hash_table[index]->name, name, TABLE_SIZE) == 0) {
    return hash_table[index];
  } else {
    return NULL;
  }
}

int main() {
  init_hash_table();
  print_table();
  person jacob = { .name="Jacob", .age=12 };
  person kate = { .name="Kate", .age=13 };
  person mpho = { .name="Mpho", .age=1 };
  hash_table_insert(&jacob);
  hash_table_insert(&kate);
  hash_table_insert(&mpho);

  person *tmp = hash_table_lookup("Mpho");
  if (tmp == NULL) {
    printf("Not found\n");
  } else {
    printf("Found %s\n", tmp->name);
  }
  tmp = hash_table_lookup("George");
  if (tmp == NULL) {
    printf("Not found\n");
  } else {
    printf("Found %s\n", tmp->name);
  }

  print_table();
  return 0;
}