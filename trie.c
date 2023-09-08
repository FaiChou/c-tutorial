#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define ALPHABET_SIZE 26

typedef struct TrieNode {
  struct TrieNode *children[ALPHABET_SIZE];
  bool isEndOfWord;
} TrieNode;

TrieNode *new_node() {
  TrieNode *newnode = malloc(sizeof(TrieNode));
  newnode->isEndOfWord = false;
  for (int i=0; i < ALPHABET_SIZE; i++) {
    newnode->children[i] = NULL;
  }
  return newnode;
}

void insert(TrieNode *root, const char *word) {
  TrieNode *current = root;
  for (int level = 0; level < strlen(word); ++level) {
    int index = word[level] - 'a';
    if (current->children[index] == NULL) {
      current->children[index] = new_node();
    }
    current = current->children[index];
  }
  current->isEndOfWord = true;
}

bool search(TrieNode *root, const char *word) {
  TrieNode *current = root;
  for (int level = 0; level < strlen(word); level++) {
    int index = word[level] - 'a';
    if (current->children[index] == NULL) {
      return false;
    }
    current = current->children[index];
  }
  return (current != NULL && current->isEndOfWord);
}

int main() {
    TrieNode *root = new_node();
    insert(root, "apple");
    insert(root, "app");
    insert(root, "bat");

    printf("%s\n", search(root, "apple") ? "Found" : "Not Found");
    printf("%s\n", search(root, "app") ? "Found" : "Not Found");
    printf("%s\n", search(root, "appl") ? "Found" : "Not Found");
    printf("%s\n", search(root, "bat") ? "Found" : "Not Found");

    return 0;
}
