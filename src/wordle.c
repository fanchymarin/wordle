#include "wordle.h"

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

void print_game_state()
{
  char letter = 0;
  char* letter_color = NULL;
  
  printf("\n");
  for (int i = 0; i < TRIES_NUM; i++)
  {
    printf("\t");
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

void print_welcome_message()
{
  
  printf("%s ____      ____   ___   _______     ______   _____     ________  \n", BOLD_GREEN);
  printf("|_  _|    |_  _|.'   `.|_   __ \\   |_   _ `.|_   _|   |_   __  | \n");
  printf("  \\ \\  /\\  / / /  .-.  \\ | |__) |    | | `. \\ | |       | |_ \\_| \n");
  printf("   \\ \\/  \\/ /  | |   | | |  __ /     | |  | | | |   _   |  _| _  \n");
  printf("    \\  /\\  /   \\  `-'  /_| |  \\ \\_  _| |_.' /_| |__/ | _| |__/ | \n");
  printf("     \\/  \\/     `.___.'|____| |___|______.''|________||________| \n");
  printf("                                                                 \n%s", COLOR_RESET);
  printf("\nYou have %d tries to guess the word\n", TRIES_NUM);
  printf("The word is %d letters long\n", WORD_SIZE);
  printf("Good luck!\n\n");
}

char *all_caps(char *word)
{
  for (int i = 0; word[i]; i++)
    word[i] = toupper((unsigned char) word[i]);
  return word;
}

bool is_wordle_word(char *word)
{
  if (!word)
    return false;

  int word_len = strlen(word);
  if (word_len != WORD_SIZE)
    return false;

  for (int i = 0; i < word_len; i++)
  {
    if (!isalpha(word[i]))
      return false;
  }
  return dict_check(wordle_data.dictionary, word); 
}