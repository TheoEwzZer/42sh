/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** minishell
*/

#include "mysh.h"

void remove_variables(var_t *var, variables_t *prev_var, variables_t *curr_var)
{
    if (!prev_var)
        var->variables = curr_var->next;
    else
        prev_var->next = curr_var->next;
    free(curr_var->variables);
    for (size_t i = 0; i < curr_var->argc; i++)
        free(curr_var->value[i]);
    free(curr_var->value);
    free(curr_var);
    return;
}

void check_variables(var_t *var, char *variables)
{
    variables_t *prev_var = NULL;
    variables_t *curr_var = var->variables;

    while (curr_var) {
        if (!strcmp(curr_var->variables, variables)) {
            remove_variables(var, prev_var, curr_var);
            return;
        }
        prev_var = curr_var;
        curr_var = curr_var->next;
    }
}

void builtin_unset(char **str, var_t *var)
{
    if (!str[1]) {
        write(2, "unset: Too few arguments.\n", 26);
        free_var(var);
        exit(EXIT_FAILURE);
    }
    for (size_t i = 1; str[i]; i++)
        check_variables(var, str[i]);
}
