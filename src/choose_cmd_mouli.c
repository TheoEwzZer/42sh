/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** minishell
*/

#include "mysh.h"

void choose_cmd_mouli4(char **str, var_t *var)
{
    if (!strncmp(str[0], "fg", 2)) {
        if (!str[1]) {
            write(2, "No job control in this shell.\n", 30);
            var->return_value = EXIT_FAILURE; return;
        } foreground_signals(str); return;
    }
    if (!strncmp(str[0], "bg", 2)) {
        if (!str[1]) {
            write(2, "No job control in this shell.\n", 30);
            var->return_value = EXIT_FAILURE; return;
        } background_signals(str); return;
    } var->pid = fork();
    if (var->pid == -1) {
        var->return_value = EXIT_FAILURE;
        free(str); exit(EXIT_FAILURE);
    }
    if (!strcmp(str[0], ">") || !strcmp(str[0], ">>")
    || !strcmp(str[0], "<") || !strcmp(str[0], "<<"))
        begin_with_redirection(str, var);
    check_not_found_and_close(str, var);
}

void choose_cmd_mouli2(char **str, var_t *var)
{
    if (!strcmp(str[0], "alias")) {
        builtin_alias(str, var);
        return;
    } if (!strcmp(str[0], "unalias")) {
        builtin_unalias(str, var);
        return;
    } if (!strcmp(str[0], "set")) {
        builtin_set(str, var, true);
        return;
    } if (!strcmp(str[0], "unset")) {
        builtin_unset(str, var);
        return;
    } if (!strcmp(str[0], "where")) {
        builtin_where(str, var);
        return;
    } if (!strcmp(str[0], "echo") && !contain_redirection(str)) {
        builtin_echo(str, var);
        return;
    }
    choose_cmd_mouli3(str, var);
}

void choose_cmd_mouli3(char **str, var_t *var)
{
    size_t len = strlen(str[0]);

    if (!strcmp(str[0], "which")) {
        builtin_which(str, var);
        return;
    }
    if (!strcmp(str[0], "history")) {
        builtin_history(var);
        return;
    }
    if (!strcmp(str[0], "foreach")) {
        builtin_foreach(str, var);
        return;
    }
    if (str[0][len - 1] == 'h' && str[0][len - 2] == 's') {
        exec_script(str, var);
        return;
    }
    choose_cmd_mouli4(str, var);
}

void choose_cmd_mouli(char **str, var_t *var)
{
    if (!strcmp(str[0], "cd")) {
        builtin_cd(str, var);
        return;
    } if (!strcmp(str[0], "exit")) {
        builtin_exit(str, var);
        return;
    } if (!strcmp(str[0], "unsetenv")) {
        builtin_unsetenv(str, var);
        return;
    } if (!strcmp(str[0], "env") || (!strcmp(str[0], "setenv")
    && (!str[1] || str[1][0] == '|' || str[1][0] == '<' || str[1][0] == '>'))) {
        str[0] = strdup("env");
        builtin_env(str, var);
        return;
    } if (!strcmp(str[0], "setenv")) {
        builtin_setenv(str, var);
        return;
    }
    choose_cmd_mouli2(str, var);
}
