NAME = syntax_tester

CC = cc
CFLAGS = -Wall -Wextra -Werror -I./../libft -I./../lexical_a/  -I./ -g -fsanitize=address

LIBFT = ../libft/libft.a
LEX_DIR = ../lexical_a/

SRC = $(LEX_DIR)token_mgmt.c $(LEX_DIR)token_setters.c analyze.c utils.c test.c
OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C ../libft

fclean:
	rm -f $(OBJS)
	rm -f $(NAME)
	$(MAKE) -C ../libft fclean

.PHONY: all fclean

