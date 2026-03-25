NAME = wordle
CC = gcc
FLAGS = -Wall -Wextra
LDLIBS = -lcurl

OBJDIR = obj
SRCDIR = src
INCDIR = inc
RESDIR = res

SOURCEFILES = main.c fetch_word.c wordle.c trie_dict.c init.c
INCLUDEFILES = wordle.h trie_dict.h

OBJECTS := $(SOURCEFILES:%.c=$(OBJDIR)/%.o)
SOURCES := $(addprefix $(SRCDIR)/, $(SOURCEFILES))
INCLUDES := $(addprefix $(INCDIR)/, $(INCLUDEFILES))

all: $(NAME)

debug: FLAGS += -g
debug: re

$(NAME): $(OBJECTS)
	$(CC) $(FLAGS) $(LDLIBS) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCLUDES)
	xxd -i $(RESDIR)/words.txt $(INCDIR)/words.h
	mkdir -p $(OBJDIR)
	$(CC) $(FLAGS) -I$(INCDIR) -c $< -o $@

clean:
	rm -rf $(OBJDIR)
	rm -rf $(INCDIR)/words.h

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: re fclean clean
