/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** minishell
*/

#include "mysh.h"

void check_builtins_where(char *str, unsigned int *found)
{
    char const *builtins[14] = {"cd", "echo", "setenv", "unsetenv", "where",
    "which", "exit", "alias", "unalias", "repeat", "history", "set",
    "unset", NULL};

    for (size_t i = 0; builtins[i]; i++) {
        if (!strcmp(str, builtins[i])) {
            write(1, str, strlen(str));
            write(1, " is a shell built-in\n", 21);
            (*found)++;
            return;
        }
    }
}
