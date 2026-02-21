NAME = wordle
CC = gcc
FLAGS = -Wall -Wextra -Werror

OBJDIR = obj
SOURCES = main.c fetch_word.c
OBJECTS := $(SOURCES:%.c=$(OBJDIR)/%.o)
LDLIBS = -lcurl

all: $(NAME)

debug: FLAGS += -g
debug: re

$(NAME): $(OBJECTS)
	$(CC) $(FLAGS) $(LDLIBS) $^ -o $@

$(OBJDIR)/%.o: %.c
	mkdir -p $(OBJDIR)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJECTS) $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: re fclean clean
