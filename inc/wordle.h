#ifndef WORDLE_H
# define WORDLE_H

# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdio.h>

# define WORDLE_URL "https://random-word-api.herokuapp.com/word?length=5&diff=2"
# define BUF_LEN 2096

char* fetch_word();

#endif
