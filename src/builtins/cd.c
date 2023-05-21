/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** minishell
*/

#include "mysh.h"

char *create_new_cwd(char *cwd)
{
    char *new_cwd = NULL;
    size_t len = strlen(cwd) + 5;

    new_cwd = calloc(len, sizeof(char));
    if (!new_cwd)
        return NULL;
    new_cwd = strcat(new_cwd, "PWD=");
    new_cwd = strcat(new_cwd, cwd);
    return new_cwd;
}

void change_cwd(char **str, var_t *var)
{
    bool has_changed = false;

    if (str[1] && (!strcmp(str[1], "home") || !strcmp(str[1], "~"))) {
        chdir(var->home);
        has_changed = true;
    } else if (str[1] && !strcmp(str[1], "-")) {
        chdir(var->old_cwd);
        has_changed = true;
    }
    if (str[1] && !has_changed)
        chdir(str[1]);
    else if (!has_changed)
        chdir(var->home);
}

char **replace_cwd(char *new_cwd, var_t *var)
{
    size_t len = my_strlen_double(var->env);
    char **str = calloc(len + 1, sizeof(char *));

    if (!str || !new_cwd)
        return NULL;
    for (size_t i = 0; var->env[i]; i++) {
        if (!strncmp(var->env[i], "PWD=", 4))
            str[i] = new_cwd;
        else
            str[i] = strdup(var->env[i]);
    }
    return str;
}

void builtin_cd(char **str, var_t *var)
{
    char *cwd = 0;

    handle_pipe(str, var);
    if (str[1] && strcmp(str[1], "-")) {
        free(var->old_cwd);
        var->old_cwd = strdup(getcwd(NULL, 0));
    }
    if (str[1])
        handle_errors_cd(str);
    change_cwd(str, var);
    cwd = getcwd(NULL, 0);
    var->env = replace_cwd(create_new_cwd(cwd), var);
    var->return_value = EXIT_SUCCESS;
}
