NAME = wordle
CC = gcc
FLAGS = -Wall -Wextra
LDLIBS = -lcurl

OBJDIR = obj
SRCDIR = src
INCDIR = inc

SOURCEFILES = main.c fetch_word.c wordle.c

OBJECTS := $(SOURCEFILES:%.c=$(OBJDIR)/%.o)
SOURCES := $(addprefix $(SRCDIR)/, $(SOURCEFILES))
INCLUDES := $(wildcard $(INCDIR)/*.h)

all: $(NAME)

debug: FLAGS += -g
debug: re

$(NAME): $(OBJECTS)
	$(CC) $(FLAGS) $(LDLIBS) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCLUDES)
	mkdir -p $(OBJDIR)
	$(CC) $(FLAGS) -I$(INCDIR) -c $< -o $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: re fclean clean
