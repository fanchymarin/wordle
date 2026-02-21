#include "wordle.h"

void wordle(char* word)
{
  printf("Word of the day: %s\n", word);
}

int main()
{
  char* word = fetch_word();

  if (word == NULL)
  {
    printf("Error fetching word\n");
    return EXIT_FAILURE;
  }

  wordle(word);
  free(word);
  return EXIT_SUCCESS;
}