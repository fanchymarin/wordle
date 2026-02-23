#ifndef WORDLE_H
# define WORDLE_H

# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <ctype.h>

# define WORDLE_URL "https://random-word-api.herokuapp.com/word?length=5&diff=2"
# define WORD_SIZE 5
# define TRIES_NUM 5

# define BUFFER_SIZE 2096

# define BOLD_GREEN "\e[1;32m"
# define BOLD_YELLOW "\e[1;33m"
# define COLOR_RESET "\e[0m"

typedef struct s_wordle_data
{
  char answer[WORD_SIZE + 1];

  char responses[TRIES_NUM][WORD_SIZE + 1];
  int response_index;
} t_wordle_data;

char* fetch_word();
int is_wordle_word(char *word);
void wordle(char* word);

#endif
