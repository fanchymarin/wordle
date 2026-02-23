#ifndef WORDLE_H
# define WORDLE_H

# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <ctype.h>

# define WORDLE_URL "https://random-word-api.herokuapp.com/word?length=5&diff=2"
# define WORD_SIZE 5
# define BUFFER_SIZE 2096

char* fetch_word();
int is_wordle_word(char *word);
void wordle(char* word);

#endif
