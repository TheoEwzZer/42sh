/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** minishell
*/

#include "mysh.h"

void found_home_and_path(var_t *var)
{
    bool found_home = false;
    bool found_path = false;

    for (size_t i = 0; var->env[i]; i++) {
        if (!found_home && !strncmp(var->env[i], "USER_ZDOTDIR=", 13)) {
            var->home = strdup(var->env[i] + 13);
            found_home = true;
        }
        if (!found_path && !strncmp(var->env[i], "PATH=", 5)) {
            var->path = NULL;
            var->path = strdup(var->env[i] + 5);
            var->path_complete = strdup(var->env[i] + 5);
            found_path = true;
        }
        if (found_home && found_path)
            break;
    }
    if (!found_home)
        var->home = "/home/";
    parsing_path(var);
}

void found_special_variables(var_t *var)
{
    bool found_term = false;

    for (size_t i = 0; var->env[i]; i++) {
        if (!found_term && !strncmp(var->env[i], "TERM=", 5)) {
            var->term = strdup(var->env[i] + 5);
            found_term = true;
        }
        if (found_term)
            break;
    }
    if (!found_term)
        var->term = strdup("xterm-256color");
}
