#include "wordle.h"

t_wordle_data wordle_data;

void init_wordle(char* word)
{
  bzero(&wordle_data, sizeof(t_wordle_data));
  strcpy(wordle_data.answer, all_caps(word));
}

int main()
{
  char* word = fetch_word();

  if (!is_wordle_word(word))
  {
    fprintf(stderr, "Error fetching word\n");
    return EXIT_FAILURE;
  }

  char input_word[BUFFER_SIZE];
  init_wordle(word);
  
  print_welcome_message();
  print_game_state();
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

    if (!is_word_valid(input_word))
    {
      printf("Word is not valid\n");
      continue;
    }

    memcpy(
      wordle_data.responses[wordle_data.response_index++],
      all_caps(input_word),
      WORD_SIZE);

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

  free(word);
  return EXIT_SUCCESS;
}