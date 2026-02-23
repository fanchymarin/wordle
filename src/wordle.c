#include "wordle.h"

char *all_caps(char *word)
{
  for (int i = 0; word[i]; i++)
    word[i] = toupper((unsigned char) word[i]);
  return word;
}

int is_wordle_word(char *word)
{
  if (!word)
    return 0;

  int word_len = strlen(word);
  if (word_len != WORD_SIZE)
    return 0;

  for (int i = 0; i < word_len; i++)
  {
    if (!isalpha(word[i]))
      return 0;
  }
  return 1; 
}

int is_word_valid(char* word)
{
  int word_len = strlen(word);
  for (int i = 0; i < word_len; i++)
  {
    if (word[i] == '\n')
      word[i] = 0;
  }

  return is_wordle_word(word);
}

void wordle(char* word)
{
  char input_word[BUFFER_SIZE];

  all_caps(word);
  printf("Wordle word: %s\n", word);

  while (1)
  {
    printf("Enter a 5-letter word: ");
    fflush(stdout);
    
    bzero(input_word, BUFFER_SIZE);
    if (fgets(input_word, BUFFER_SIZE, stdin) == NULL)
    {
      perror("Error getting input");
      break;
    }

    if (!is_word_valid(input_word))
    {
      printf("Word is not valid\n");
      continue;
    }
  }
}