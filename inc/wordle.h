#ifndef WORDLE_H
# define WORDLE_H

# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdio.h>

# define WORDLE_URL "https://a04-wordle-api.vercel.app/api/random-word"
# define BUF_LEN 2096

char* fetch_word();

#endif
