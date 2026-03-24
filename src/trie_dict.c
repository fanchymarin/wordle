#include "trie_dict.h"

t_trie_node *trie_create_node() 
{
  return calloc(1, sizeof (t_trie_node));
}

bool dict_insert(t_trie_node **root, char* word)
{
  if (*root == NULL)
  {
    *root = trie_create_node();
  }

  t_trie_node *tmp = *root;

  for (int i = 0; word[i]; i++)
  {
    if (!isalpha(word[i]))
    {
      fprintf(stderr, "Error inserting word: is not alphabetical\n");
      exit(EXIT_FAILURE);
    }

    t_trie_node **char_node = &tmp->children[CHAR_IDX(word[i])];
    if (*char_node == NULL)
    {
      *char_node = trie_create_node();
    }
    tmp = *char_node;
  }
  if (tmp->terminal)
  {
    return false;
  }
  tmp->terminal = true;
  return tmp->terminal;
}

bool dict_check(t_trie_node *root, char* word)
{
  for (int i = 0; word[i]; i++)
  {
    if (!isalpha(word[i]))
    {
      fprintf(stderr, "Error checking word: is not alphabetical\n");
      exit(EXIT_FAILURE);
    }

    t_trie_node *char_node = root->children[TO_INDEX(word[i])];
    if (char_node == NULL)
    {
      return false;
    }
    root = char_node;
  }
  if (root->terminal)
  {
    return true;
  }
  return false;
}

void print_trie_rec(t_trie_node *node, unsigned char *prefix, int length)
{
  unsigned char new_prefix[length + 2];
  memcpy(new_prefix, prefix, length);
  new_prefix[length + 1] = 0;

  if (node->terminal)
  {
    printf("%s\n", prefix);
  }

  for (int i = 0; i < NUM_CHARS; i++)
  {
    if (node->children[i] != NULL)
    {
      new_prefix[length] = TO_CHAR(i);
      print_trie_rec(node->children[i], new_prefix, length + 1);
    }
  }
}

void print_trie(t_trie_node *root)
{
  if (root == NULL)
  {
    printf("Empty trie\n");
    return ;
  }
  print_trie_rec(root, NULL, 0);
}