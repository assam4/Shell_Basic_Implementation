#include "syntax.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char input[1024];
    t_list *tokens = NULL;

    // Read command from stdin
    printf("Enter a command: ");
    if (!fgets(input, sizeof(input), stdin))
        return (1);

    // Remove the newline character from the end of the string
    input[strcspn(input, "\n")] = '\0';

    // Tokenization
    if (!get_tokens(input, &tokens)) {
        ft_putstr_fd("❌ Tokenization error\n", STDERR_FILENO);
        return (1);
    }

    // Syntax analysis
    if (!syntax_analyse(tokens)) {
        ft_putstr_fd("❌ Syntax error\n", STDERR_FILENO);
    } else {
        ft_putstr_fd("✅ Syntax is correct\n", STDOUT_FILENO);
    }

    // Clear the token list
    ft_lstclear(&tokens, token_free);

    return 0;
}

