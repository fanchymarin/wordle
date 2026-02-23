#include "wordle.h"

t_wordle_data wordle_data;

char *select_color(char c, int c_pos)
{
  char *selected_color = calloc(8, sizeof(char));
  
  if (!c)
    return selected_color;

  for (int i = 0; wordle_data.answer[i]; i++)
  {
    if (wordle_data.answer[i] == c)
    {
      memcpy(selected_color, BOLD_YELLOW, 8);
      if (i == c_pos)
        return memcpy(selected_color, BOLD_GREEN, 8);
    }
  }
  return selected_color;
}

void print_game()
{
  char letter = 0;
  char* letter_color = NULL;
  
  printf("\n");
  for (int i = 0; i < TRIES_NUM; i++)
  {
    for (int j = 0; j < WORD_SIZE; j++)
    {
      letter = wordle_data.responses[i][j];
      letter_color = select_color(letter, j);
      printf("%s%c%s ",
        letter_color,
        letter ? letter : '_',
        COLOR_RESET);
      free(letter_color);
    }
    printf("\n");
  }
  printf("\n");
}

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

  bzero(&wordle_data, sizeof(t_wordle_data));
  strcpy(wordle_data.answer, all_caps(word));
  print_game();

  while (wordle_data.response_index < TRIES_NUM)
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

    memcpy(wordle_data.responses[wordle_data.response_index++], all_caps(input_word), WORD_SIZE);
    print_game();
  }
}