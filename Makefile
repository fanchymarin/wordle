NAME = wordle
CC = gcc
FLAGS = -Wall -Wextra -Werror

OBJDIR = obj
SOURCES = main.c
OBJECTS := $(SOURCES:%.c=$(OBJDIR)/%.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(FLAGS) $^ -o $@

$(OBJDIR)/%.o: %.c
	mkdir -p $(OBJDIR)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJECTS) $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: re fclean clean
