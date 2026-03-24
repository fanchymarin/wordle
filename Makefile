NAME = wordle
CC = gcc
FLAGS = -Wall -Wextra
LDLIBS = -lcurl

OBJDIR = obj
SRCDIR = src
INCDIR = inc
RESDIR = res

SOURCEFILES = main.c fetch_word.c wordle.c trie_dict.c

OBJECTS := $(SOURCEFILES:%.c=$(OBJDIR)/%.o)
SOURCES := $(addprefix $(SRCDIR)/, $(SOURCEFILES))
INCLUDES := $(wildcard $(INCDIR)/*.h)

all: $(NAME)

debug: FLAGS += -g
debug: re

$(NAME): $(OBJECTS)
	$(CC) $(FLAGS) $(LDLIBS) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCLUDES)
	xxd -i $(RESDIR)/words.txt $(RESDIR)/words.h
	mkdir -p $(OBJDIR)
	$(CC) $(FLAGS) -I$(INCDIR) -c $< -o $@

clean:
	rm -rf $(OBJDIR)
	rm -rf $(RESDIR)/words.h

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: re fclean clean
