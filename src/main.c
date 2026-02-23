#include "wordle.h"

int main()
{
  char* word = fetch_word();

  if (!is_wordle_word(word))
  {
    fprintf(stderr, "Error fetching word\n");
    return EXIT_FAILURE;
  }

  wordle(word);
  free(word);
  return EXIT_SUCCESS;
}