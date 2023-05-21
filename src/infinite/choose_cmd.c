/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** minishell
*/

#include "mysh.h"

void choose_cmd_4(char **str, var_t *var)
{
    if (!strncmp(var->input, "fg", 2)) {
        if (!str[1]) {
            write(2, "fg: No current job.\n", 20);
            var->return_value = EXIT_FAILURE;
            return;
        }
        foreground_signals(str);
        return;
    }
    if (!strncmp(var->input, "bg", 2)) {
        if (!str[1]) {
            write(2, "bg: No current job.\n", 20);
            var->return_value = EXIT_FAILURE;
            return;
        }
        background_signals(str);
        return;
    }
    check(str, var);
}

void choose_cmd3(char **str, var_t *var)
{
    if (!strncmp(var->input, "unset", 5)) {
        builtin_unset(str, var);
        return;
    }
    if (!strncmp(var->input, "where", 5)) {
        builtin_where(str, var);
        return;
    }
    if (!strncmp(var->input, "which", 5)) {
        builtin_which(str, var);
        return;
    }
    if (!strncmp(var->input, "history", 7)) {
        builtin_history(var);
        return;
    }
    if (!strcmp(str[0], "foreach")) {
        builtin_foreach(str, var);
        return;
    } choose_cmd_4(str, var);
}

void choose_cmd2(char **str, var_t *var)
{
    if (!strncmp(var->input, "env", 3)) {
        builtin_env(str, var);
        return;
    }
    if (!strncmp(var->input, "echo", 4) && !contain_redirection(str)) {
        builtin_echo(str, var);
        return;
    }
    if (!strncmp(var->input, "alias", 5)) {
        builtin_alias(str, var);
        return;
    }
    if (!strncmp(var->input, "unalias", 7)) {
        builtin_unalias(str, var);
        return;
    }
    if (!strncmp(var->input, "set", 3)) {
        builtin_set(str, var, true);
        return;
    } choose_cmd3(str, var);
}

void choose_cmd(char **str, var_t *var)
{
    if (!strncmp(var->input, "!!", 2)) {
        var->input = var->history[var->hist_value - 2];
        str[0] = var->history[var->hist_value - 2];
        if (str[0][strlen(str[0]) - 1] == '\n')
            str[0][strlen(str[0]) - 1] = '\0';
    } if (!strncmp(var->input, "!", 1)) {
        var->input = choose_command_history(var, str);
        str[0] = choose_command_history(var, str);
        str[0][strlen(str[0]) - 1] = '\0';
    } if (!strncmp(var->input, "cd", 2)) {
        builtin_cd(str, var); return;
    } if (!strncmp(var->input, "exit", 4)) {
        builtin_exit(str, var); return;
    } if (!strncmp(var->input, "unsetenv", 8)) {
        builtin_unsetenv(str, var);
        return;
    } if (!strncmp(var->input, "setenv", 6)) {
        builtin_setenv(str, var);
        return;
    } choose_cmd2(str, var);
}
