#ifndef TRIE_DICT_H
#define TRIE_DICT_H

// Only for isalpha() chars
#define NUM_CHARS 52
#define TO_INDEX(c) c - 65
#define TO_CHAR(i) i + 65

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

typedef struct s_trie_node {
  struct s_trie_node *children[NUM_CHARS];
  bool terminal;
} t_trie_node;

bool dict_insert(t_trie_node **root, char* word);
bool dict_check(t_trie_node *root, char* word);
void dict_print(t_trie_node *root);

#endif