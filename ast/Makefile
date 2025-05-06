NAME = ast_tester

CC = cc

INC = -I./../libft -I./../lexical_a -I.

CFLAGS = -Wall -Wextra -Werror / -g -fsanitize=address

LIBFT = ../libft/libft.a

SRC = $(shell find . -name "*.c")

OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
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

