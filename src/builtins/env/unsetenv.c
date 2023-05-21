/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** minishell
*/

#include "mysh.h"

void remove_env(char **str, size_t j, var_t *var)
{
    bool found = false;
    size_t len = strlen(str[j]);

    for (size_t i = 0; var->env[i]; i++) {
        if (!strncmp(var->env[i], str[j], len) && var->env[i][len] == '=')
            found = true;
        if (found)
            var->env[i] = var->env[i + 1] ? var->env[i + 1] : NULL;
    }
}

void builtin_unsetenv(char **str, var_t *var)
{
    if (!str[1]) {
        write(2, "unsetenv: Too few arguments.\n", 29);
        free_var(var);
        exit(EXIT_FAILURE);
    }
    for (size_t j = 1; str[j]; j++)
        remove_env(str, j, var);
}
