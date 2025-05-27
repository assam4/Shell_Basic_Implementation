MAKEFLAGS		= --no-print-directory

NAME			= minishell

SRC				= $(shell find . -path "./library/libft" -prune -o -name "*.c" ! -name "test.c" -print)

INC				= $(shell find . \( -name ".git" -o -name ".vscode" \) -prune -o -type d -print | sed 's|^|-I |')

HEADERS			= $(shell find . -name "*.h")

BUILD_DIR		= ./.build

OBJ =			$(SRC:%.c=$(BUILD_DIR)/%.o)

FLAGS			= -Wall -Wextra -Werror -g3 -fsanitize=address

RLFLAGS			= -lreadline

LIBFT_DIR		= ./library/libft

LIBFT			= -L$(LIBFT_DIR) -lft

RED			= \e[31m
GREEN		= \e[32m
YELLOW		= \e[33m
RESET		= \e[0m

all: build lib $(NAME)

$(BUILD_DIR)/%.o: %.c $(HEADERS) Makefile
	@mkdir -p $(dir $@)
	@$(CC) $(FLAGS) $(INC) -c $< -o $@
	@echo "  ✅ ${GREEN}./$<${RESET}"

$(NAME): $(OBJ) $(LIBFT_DIR)/libft.a
	@cc $(FLAGS) $(INC) $(OBJ) $(RLFLAGS) -o $(NAME) $(LIBFT_DIR)/libft.a
	@echo "${YELLOW}Minishell Done!${RESET}\n"

build:
	@mkdir -p $(BUILD_DIR)

lib:
	@make -C $(LIBFT_DIR)

clean:
	@echo "🧹 $(RED)Cleaning object files...$(RESET)"
	@rm -rf $(BUILD_DIR)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	@echo "🗑️  $(RED)Removing binary: $(NAME)$(RESET)"
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

re:	fclean all

.PHONY: all build lib clean fclean re
