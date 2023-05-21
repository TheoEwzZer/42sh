/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** minishell
*/

#include "mysh.h"

bool check_command_not_found(char **str, var_t *var)
{
    if (str[0][0] != '/' && str[0][0] != '.' && !var->actu_path) {
        if (strcmp(str[0], "cd") &&
            strcmp(str[0], "exit") &&
            strcmp(str[0], "env") &&
            strcmp(str[0], "setenv") &&
            strcmp(str[0], "echo") &&
            strcmp(str[0], "alias") &&
            strcmp(str[0], "where") &&
            strcmp(str[0], "which") &&
            strcmp(str[0], "history") &&
            strcmp(str[0], "foreach") &&
            strcmp(str[0], "unsetenv")) {
                write(2, str[0], strlen(str[0]));
                write(2, ": Command not found.\n", 21);
                var->return_value = EXIT_FAILURE;
                return true;
        }
    }
    return false;
}

void check_arg(int argc)
{
    if (argc != 1)
        exit(EXIT_FAILURE);
}

void write_cmd(char *cmd)
{
    if (!access(cmd, F_OK)) {
        write(1, cmd, strlen(cmd));
        write(1, "\n", 1);
    }
}

char *my_strtok_r(char *str, const char *delim, char **saveptr)
{
    char *token = NULL;
    char *last = NULL;

    if (str)
        *saveptr = str;
    if (!(*saveptr) || !(**saveptr))
        return NULL;
    token = *saveptr;
    last = strstr(token, delim);
    while (last) {
        *last = '\0';
        *saveptr = last + strlen(delim);
        return token;
    }
    *saveptr = NULL;
    return token;
}

bool contain_redirection(char **str)
{
    for (size_t i = 0; str[i]; i++) {
        if (!strcmp(str[i], ">") || !strcmp(str[i], ">>") ||
        !strcmp(str[i], "<") || !strcmp(str[i], "<<")) {
            return true;
        }
    }
    return false;
}
