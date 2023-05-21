/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** minishell
*/

#include "mysh.h"

void remove_alias(var_t *var, alias_t *prev_alias, alias_t *curr_alias)
{
    if (!prev_alias)
        var->alias = curr_alias->next;
    else
        prev_alias->next = curr_alias->next;
    free(curr_alias->alias);
    for (size_t i = 0; i < curr_alias->argc; i++)
        free(curr_alias->command[i]);
    free(curr_alias->command);
    free(curr_alias);
    return;
}

void check_alias(var_t *var, char *alias)
{
    alias_t *prev_alias = NULL;
    alias_t *curr_alias = var->alias;

    while (curr_alias) {
        if (!strcmp(curr_alias->alias, alias)) {
            remove_alias(var, prev_alias, curr_alias);
            return;
        }
        prev_alias = curr_alias;
        curr_alias = curr_alias->next;
    }
}

void builtin_unalias(char **str, var_t *var)
{
    if (!str[1]) {
        write(2, "unalias: Too few arguments.\n", 28);
        free_var(var);
        exit(EXIT_FAILURE);
    }
    for (size_t i = 1; str[i]; i++)
        check_alias(var, str[i]);
}
