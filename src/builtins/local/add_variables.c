/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** minishell
*/

#include "mysh.h"

void update_variables(variables_t *variables, char **value)
{
    size_t argc = 0;

    while (value[argc])
        argc++;
    if (value[0][0] == '\"') {
        value[0]++;
        if (value[argc - 1][strlen(value[argc - 1]) - 1] == '\"')
            value[argc - 1][strlen(value[argc - 1]) - 1] = '\0';
    }
    for (size_t i = 0; i < variables->argc; i++)
        free(variables->value[i]);
    free(variables->value);
    variables->value = calloc(argc + 1, sizeof(char *));
    for (size_t i = 0; i < argc; i++)
        variables->value[i] = strdup(value[i]);
    variables->argc = argc;
}

void create_new_variables(var_t *var, const char *variables, char **value)
{
    variables_t *new_variables = malloc(sizeof(variables_t));
    size_t argc = 0;

    while (value[argc])
        argc++;
    if (value[0][0] == '\"') {
        value[0]++;
        if (value[argc - 1][strlen(value[argc - 1]) - 1] == '\"')
            value[argc - 1][strlen(value[argc - 1]) - 1] = '\0';
    }
    new_variables->variables = strdup(variables);
    new_variables->value = calloc(argc + 1, sizeof(char *));
    for (size_t i = 0; i < argc; i++)
        new_variables->value[i] = strdup(value[i]);
    new_variables->argc = argc;
    new_variables->next = var->variables;
    var->variables = new_variables;
}

void add_variables(var_t *var, const char *variables, char **value)
{
    variables_t *variables_ptr = var->variables;

    while (variables_ptr) {
        if (!strcmp(variables_ptr->variables, variables)) {
            update_variables(variables_ptr, value);
            return;
        }
        variables_ptr = variables_ptr->next;
    }
    create_new_variables(var, variables, value);
}
