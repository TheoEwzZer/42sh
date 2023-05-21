/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** minishell
*/

#include "mysh.h"

int my_char_isalpha(char c)
{
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

int starts_with_digit_and_has_alnum(char *str)
{
    int has_letter = 0;

    if (!my_char_isnum(str[0]))
        return EXIT_SUCCESS;
    for (size_t i = 1; str[i]; i++) {
        if (!my_char_isalpha(str[i]) && !my_char_isnum(str[i]))
            continue;
        if (my_char_isalpha(str[i]))
            has_letter = 1;
    }
    return has_letter;
}

void builtin_exit2(char **str, var_t *var)
{
    int exit_status = atoi(str[1]);

    if (starts_with_digit_and_has_alnum(str[1])) {
        write(2, "exit: Badly formed number.\n", 27);
        free_var(var);
        exit(EXIT_FAILURE);
    }
    if ((!str[2] || !strcmp(str[2], "|"))
    && (exit_status || !strcmp(str[1], "0"))) {
        if (isatty(STDIN_FILENO))
            write(1, "exit\n", 5);
        free_var(var);
        exit(exit_status);
    }
    write(1, "exit: Expression Syntax.\n", 25);
    free_var(var);
    exit(EXIT_FAILURE);
}

void builtin_exit(char **str, var_t *var)
{
    chdir(var->cwd);
    if (!str[1]) {
        if (isatty(STDIN_FILENO))
            write(1, "exit\n", 5);
        free_var(var);
        exit(EXIT_SUCCESS);
    }
    builtin_exit2(str, var);
}
