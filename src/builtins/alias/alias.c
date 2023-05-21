/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** minishell
*/

#include "mysh.h"

void builtin_alias(char **str, var_t *var)
{
    char **command = NULL;
    char *alias = NULL;
    size_t argc = 0;

    if (!str[1]) {
        print_alias(var);
        return;
    }
    if (!str[2])
        return;
    alias = strdup(str[1]);
    for (size_t i = 2; str[i]; i++) {
        argc++;
        command = realloc(command, sizeof(char *) * argc);
        command[argc - 1] = strdup(str[i]);
    }
    argc++;
    command = realloc(command, sizeof(char *) * argc);
    command[argc - 1] = NULL;
    add_alias(var, alias, command);
}

char **get_alias(var_t *var, char *command, size_t *argc)
{
    alias_t *current_alias = NULL;

    if (!var->alias)
        return NULL;
    current_alias = var->alias;
    while (current_alias) {
        if (!strcmp(command, current_alias->alias)) {
            (*argc) = current_alias->argc;
            return current_alias->command;
        }
        current_alias = current_alias->next;
    }
    return NULL;
}

void expand_alias(char ***str_ptr, char **command, size_t i, size_t argc)
{
    char **str = *str_ptr;

    str = realloc(str, sizeof(char *) * (i + argc + 1));
    (*str_ptr) = str;
    for (size_t j = 1; j < argc; j++)
        str[i + j] = strdup(command[j]);
    str[i + argc] = NULL;
}

void replace_with_alias(var_t *var, char ***str_ptr)
{
    char **command = NULL;
    size_t argc = 0;
    char **str = *str_ptr;

    if (!var->alias)
        return;
    if (!strcmp(str[0], "alias") || !strcmp(str[0], "unalias")
    || !strcmp(str[0], "where") || !strcmp(str[0], "which"))
        return;
    for (size_t i = 0; str[i]; i++) {
        command = get_alias(var, str[i], &argc);
        if (command) {
            free(str[i]);
            str[i] = strdup(command[0]);
            expand_alias(str_ptr, command, i, argc);
            str = *str_ptr;
            i += argc - 1;
        }
    }
}

void print_alias(var_t *var)
{
    alias_t *current_alias = NULL;
    size_t len = 0;

    if (!var->alias) {
        write(2, "No aliases.\n", 12);
        return;
    }
    current_alias = var->alias;
    while (current_alias) {
        write(1, current_alias->alias, strlen(current_alias->alias));
        write(1, "\t", 1);
        write(1, current_alias->command[0], strlen(current_alias->command[0]));
        for (size_t i = 1; i < current_alias->argc; i++) {
            write(1, " ", 1);
            len = strlen(current_alias->command[i]);
            write(1, current_alias->command[i], len);
        }
        write(1, "\n", 1);
        current_alias = current_alias->next;
    }
}
