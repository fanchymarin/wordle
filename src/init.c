#include "wordle.h"
#include "words.h"

extern unsigned char res_words_txt[];
extern unsigned int res_words_txt_len;

t_trie_node *load_dictionary()
{
  if (res_words_txt_len == 0)
  {
    fprintf(stderr, "Error loading dictionary: Empty file\n");
    exit(EXIT_FAILURE);
  }

  t_trie_node *dictionary = NULL;
  char *current_line = (char *)res_words_txt;

  for (char *next_line = strchr(current_line, '\n'); next_line; next_line = strchr(current_line, '\n'))
  {
    *next_line = 0;
    if (strlen(current_line) == WORD_SIZE)
    {
      dict_insert(&dictionary, current_line);
    }
    *next_line = '\n';
    current_line = next_line + 1;
  }
  return dictionary;
}

char *load_random_word()
{
  // TODO: fetch random word from dict when fetching from API fails
  exit(1);
  //return dict_fetch_random();
}

int init_wordle()
{
  bzero(&wordle_data, sizeof(t_wordle_data));
  wordle_data.dictionary = load_dictionary();
  char* word = all_caps(fetch_word());

  if (!is_wordle_word(word))
  {
    fprintf(stderr, "Error fetching word\n");
    free(word);
    word = load_random_word();
  }

  strcpy(wordle_data.answer, word);
  free(word);
  
  print_welcome_message();
  print_game_state();
  return EXIT_SUCCESS;
}