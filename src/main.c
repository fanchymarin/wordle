#include "wordle.h"

t_wordle_data wordle_data;

int main()
{
  char input_word[BUFFER_SIZE];

  init_wordle();
  while (1)
  {
    printf("wordle> ");
    fflush(stdout);
    
    bzero(input_word, BUFFER_SIZE);
    if (fgets(input_word, BUFFER_SIZE, stdin) == NULL)
    {
      perror("Error getting input");
      break;
    }

    input_word[strlen(input_word) - 1] = 0;
    all_caps(input_word);

    if (!is_wordle_word(input_word))
    {
      printf("Word is not valid\n");
      continue;
    }

    memcpy(
      wordle_data.responses[wordle_data.response_index++],
      all_caps(input_word),
      WORD_SIZE
    );

    print_game_state();

    if (!strcmp(
      wordle_data.responses[wordle_data.response_index - 1], wordle_data.answer))
    {
      printf("%sCongratulations!%s 🎉 You've guessed the word!\n", GREEN, COLOR_RESET);
      break;
    }
    else if (wordle_data.response_index == TRIES_NUM)
    {
      printf("%sGame over!%s The answer was: %s\n", RED, COLOR_RESET, wordle_data.answer);
      break;
    }
  }
  return EXIT_SUCCESS;
}