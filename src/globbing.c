/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** minishell
*/

#include "mysh.h"

bool contains_globbing(char *str)
{
    if (!str)
        return false;
    for (size_t i = 0; str[i]; i++) {
        if (str[i] == '*' || str[i] == '?' || str[i] == '[' || str[i] == ']')
            return true;
    }
    return false;
}

void globbing(char **str, var_t *var)
{
    glob_t globbuf = {0};
    int glob_status = 0, status = 0;

    if (str[1] && contains_globbing(str[1])) {
        glob_status = glob(str[1], GLOB_NOCHECK, NULL, &globbuf);
        if (!glob_status && globbuf.gl_pathc > 0)
            str[1] = globbuf.gl_pathv[0];
        if (access(str[1], F_OK) == -1) {
            write(1, str[0], strlen(str[0]));
            write(1, ": No match.\n", 12);
            exit(EXIT_FAILURE);
        }
    }
    status = execve(var->cmd, str, var->env);
    globfree(&globbuf);
    if (status == -1) {
        try_path(str, var);
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}
