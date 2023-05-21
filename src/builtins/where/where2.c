/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** minishell
*/

#include "mysh.h"

bool error_where(char **str, var_t *var)
{
    if (!str[1]) {
        write(2, "where: Too few arguments.\n", 26);
        var->return_value = EXIT_FAILURE;
        return true;
    }
    return false;
}

bool where_slash(char *str, var_t *var)
{
    unsigned int num_slashes = 0;

    for (size_t i = 0; str[i]; i++) {
        if (str[i] == '/')
            num_slashes++;
    }
    if (num_slashes > 0) {
        write(2, "where: / in command makes no sense\n", 35);
        var->return_value = EXIT_FAILURE;
        return true;
    }
    return false;
}

void check_access(char *cmd, unsigned int *found)
{
    if (!access(cmd, F_OK)) {
        (*found)++;
        write(1, cmd, strlen(cmd));
        write(1, "\n", 1);
    }
}

char *my_strcat_malloc(char const *dest, char const *src)
{
    char *newstr = calloc(sizeof(char), (strlen(dest) + strlen(src)) + 1);
    size_t i = 0;
    size_t j = 0;

    while (dest[i]) {
        newstr[i] = dest[i];
        i++;
    }
    while (src[j]) {
        newstr[i] = src[j];
        j++;
        i++;
    }
    return newstr;
}

void check_alias_where(var_t *var, char **str, size_t i, unsigned int *found)
{
    char **alias = NULL;
    size_t argc = 0;

    alias = get_alias(var, str[i], &argc);
    if (alias) {
        (*found)++;
        write(1, str[i], strlen(str[i]));
        write(1, " is aliased to", 14);
        for (size_t j = 0; alias[j]; j++) {
            write(1, " ", 1);
            write(1, alias[j], strlen(alias[j]));
        }
        write(1, "\n", 1);
    }
}
