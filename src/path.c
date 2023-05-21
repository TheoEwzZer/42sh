/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** minishell
*/

#include "mysh.h"

void try_path2(char **str)
{
    if (str[0][0] == '!') {
        str[0]++;
        if (str[0][0] == '!')
            str[0][0] = '0';
        write(2, str[0], strlen(str[0]));
        write(2, ": Event not found.\n", 19);
        exit(EXIT_FAILURE);
    }
    if (str[0][0] == '$')
        return;
    write(2, str[0], strlen(str[0]));
    if (errno == ENOEXEC) {
        write(2, ": Exec format error. Wrong Architecture.\n", 41);
        exit(EXIT_FAILURE);
    } if (errno == EACCES) {
        write(2, ": Permission denied.\n", 21);
        exit(EXIT_FAILURE);
    }
    write(2, ": Command not found.\n", 21);
    exit(EXIT_FAILURE);
}

void try_path(char **str, var_t *var)
{
    struct stat st;
    stat(str[0], &st);
    if (var->cmd) {
        if (var->actu_path)
            var->actu_path = strtok(NULL, ":");
        var->cmd = NULL;
        if (var->actu_path)
            create_cmd(var, str);
        check_not_found_and_close(str, var);
        exit(EXIT_FAILURE);
    }
    execve(str[0], str, var->env);
    try_path2(str);
}

void parsing_path(var_t *var)
{
    const char *delim = ":";

    if (var->path)
        var->actu_path = strtok(var->path, delim);
}
