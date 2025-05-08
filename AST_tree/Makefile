NAME = ast_tester

CC = cc

INC = -I./../libft -I../syntax_a -I../lexical_a -I.

CFLAGS = -Wall -Wextra -Werror $(INC)

LIBFT = ../libft/libft.a

SRC = ../lexical_a/token_setters.c ../lexical_a/token_mgmt.c \
      ../syntax_a/analyze.c getters.c blossom.c test.c

OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS) Makefile
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C ../libft bonus

fclean:
	rm -f $(OBJS)
	rm -f $(NAME)
	$(MAKE) -C ../libft fclean

.PHONY: all fclean
