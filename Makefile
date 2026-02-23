NAME = wordle
CC = gcc
FLAGS = -Wall -Wextra
LDLIBS = -lcurl

OBJDIR = obj
SRCDIR = src
INCDIR = inc

SOURCES = main.c fetch_word.c wordle.c
OBJECTS := $(SOURCES:%.c=$(OBJDIR)/%.o)

all: $(NAME)

debug: FLAGS += -g
debug: re

$(NAME): $(OBJECTS)
	$(CC) $(FLAGS) $(LDLIBS) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(OBJDIR)
	$(CC) $(FLAGS) -I$(INCDIR) -c $< -o $@

clean:
	rm -rf $(OBJECTS) $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: re fclean clean
