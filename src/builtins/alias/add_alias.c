/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** minishell
*/

#include "mysh.h"

void update_alias(alias_t *alias, char **command)
{
    size_t argc = 0;

    while (command[argc])
        argc++;
    if (command[0][0] == '\"') {
        command[0]++;
        if (command[argc - 1][strlen(command[argc - 1]) - 1] == '\"')
            command[argc - 1][strlen(command[argc - 1]) - 1] = '\0';
    }
    for (size_t i = 0; i < alias->argc; i++)
        free(alias->command[i]);
    free(alias->command);
    alias->command = calloc(argc + 1, sizeof(char *));
    for (size_t i = 0; i < argc; i++)
        alias->command[i] = strdup(command[i]);
    alias->argc = argc;
}

void create_new_alias(var_t *var, char *alias, char **command)
{
    alias_t *new_alias = malloc(sizeof(alias_t));
    size_t argc = 0;

    while (command[argc])
        argc++;
    if (command[0][0] == '\"') {
        command[0]++;
        if (command[argc - 1][strlen(command[argc - 1]) - 1] == '\"')
            command[argc - 1][strlen(command[argc - 1]) - 1] = '\0';
    }
    new_alias->alias = strdup(alias);
    new_alias->command = calloc(argc + 1, sizeof(char *));
    for (size_t i = 0; i < argc; i++)
        new_alias->command[i] = strdup(command[i]);
    new_alias->argc = argc;
    new_alias->next = var->alias;
    var->alias = new_alias;
}

void add_alias(var_t *var, char *alias, char **command)
{
    alias_t *alias_ptr = var->alias;

    while (alias_ptr) {
        if (!strcmp(alias_ptr->alias, alias)) {
            update_alias(alias_ptr, command);
            return;
        }
        alias_ptr = alias_ptr->next;
    }
    create_new_alias(var, alias, command);
}
