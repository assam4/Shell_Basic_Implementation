NAME = lexical_tester

CC = cc
CFLAGS = -Wall -Wextra -Werror -I./../libft -I./ -g -fsanitize=address

LIBFT = ../libft/libft.a

SRC = token_mgmt.c token_setters.c test.c
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

