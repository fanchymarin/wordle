#include "wordle.h"

void welcome_message()
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

int main()
{
  welcome_message();
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