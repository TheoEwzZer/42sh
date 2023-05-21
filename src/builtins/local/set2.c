/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** minishell
*/

#include "mysh.h"

void undefine_var(var_t *var, char **str, size_t i)
{
    if (!strcmp(str[i], "$?"))
        return;
    str[i]++;
    write(1, str[i], strlen(str[i]));
    write(1, ": Undefined variable.\n", 22);
    var->return_value = EXIT_FAILURE;
    exit(EXIT_FAILURE);
}

void replace_with_variables(var_t *var, char ***str_ptr)
{
    char **command = NULL; size_t argc = 0; char **str = *str_ptr;
    if (!var->variables || !str || !str[0])
        return;
    if (!strcmp(str[0], "set") || !strcmp(str[0], "unset"))
        return;
    for (size_t i = 0; str[i]; i++) {
        if (str[i][0] != '$')
            continue;
        if (str[i][strlen(str[i]) - 1] == '\"')
            str[i][strlen(str[i]) - 1] = '\0';
        command = get_variables(var, str[i], &argc);
        if (command) {
            free(str[i]);
            str[i] = strdup(command[0]);
            expand_variables(str_ptr, command, i, argc);
            str = *str_ptr;
            i += argc - 1;
        } else
            undefine_var(var, str, i);
    }
}

void create_variables(var_t *var)
{
    char *path = NULL;
    char *paths[] = {path, NULL};

    paths[0] = strdup(var->cwd);
    add_variables(var, "PWD", paths);
    add_variables(var, "cwd", paths);
    paths[0] = strdup(var->term);
    add_variables(var, "term", paths);
    add_variables(var, "TERM", paths);
    if (!var->variables || !var->path_complete)
        return;
    paths[0] = strdup(var->path_complete);
    add_variables(var, "PATH", paths);
    for (size_t i = 0; paths[0][i]; i++) {
        if (paths[0][i] == ':')
            paths[0][i] = ' ';
    }
    add_variables(var, "path", paths);
    free(path);
}
