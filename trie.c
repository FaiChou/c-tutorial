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

// there's a bug here, the function will delete from the bottom of
// the struct recursively
// but it not check if the item(not the last one) is endofword
// for example, if `apple` and `app` in the structure, then you want to
// delete the `apple`, this function will delete `app` as well
bool delete(TrieNode* current, const char* word, int level, int length) {
    if (current == NULL) {
        return false;
    }
    if (level == length) {
        if (current->isEndOfWord) {
            current->isEndOfWord = false;
            return true;
        }
        return false;
    }
    int index = word[level] - 'a';
    if (delete(current->children[index], word, level + 1, length)) {
        // 递归删除后，检查该节点是否还有其他子节点
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            if (current->children[index]->children[i] != NULL) {
                return true;
            }
        }
        // 如果没有其他子节点，释放该节点
        free(current->children[index]);
        current->children[index] = NULL;
        return true;
    }
    return false;
}

void log_trie(TrieNode *node, const char buffer[]) {
  if (node == NULL) {
    printf("DONE\n");
    return;
  }
  if (node->isEndOfWord) {
    printf("%s\n", buffer);
  }
  for (int i=0; i < ALPHABET_SIZE; ++i) {
    if (node->children[i] != NULL) {
      char newbuffer[strlen(buffer)+2];
      sprintf(newbuffer, "%s%c", buffer, (i+'a'));
      log_trie(node->children[i], newbuffer);
    }
  }
}

int main() {
    TrieNode* root = new_node();
    insert(root, "apple");
    insert(root, "app");
    insert(root, "bat");
    log_trie(root, "");
    printf("%s\n", search(root, "apple") ? "Found" : "Not Found");  // Output: Found
    printf("%s\n", search(root, "app") ? "Found" : "Not Found");    // Output: Found
    printf("%s\n", search(root, "appp") ? "Found" : "Not Found");   // Output: Not Found
    printf("%s\n", search(root, "bat") ? "Found" : "Not Found");    // Output: Found

    delete(root, "app", 0, strlen("app"));

    printf("%s\n", search(root, "apple") ? "Found" : "Not Found");  // Output: Found
    printf("%s\n", search(root, "bat") ? "Found" : "Not Found");    // Output: Found
    printf("%s\n", search(root, "app") ? "Found" : "Not Found");    // Output: Not Found

    insert(root, "cde");
    insert(root, "applea");
    insert(root, "appa");
    insert(root, "xpp");
    log_trie(root, "");
    return 0;
}
