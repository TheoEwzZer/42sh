/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** minishell
*/

#include "mysh.h"

bool check_backticks2(char **str2, size_t k, char *last)
{
    if (!str2 || !str2[k])
        return false;
    if (str2[k][strlen(str2[k]) - 1] == '`') {
        last = str2[k];
        last[strlen(last) - 1] = '\0';
        if (str2[k + 1])
            str2[k + 1] = NULL;
        return true;
    }
    return false;
}

void check_backticks(char **str, var_t *var, size_t *i)
{
    char *last = NULL;
    char **str2 = strdup_double(str);
    size_t k = 0;

    if (!str2)
        return;
    for (size_t j = 0; j < *i; j++)
        str2++;
    if (!str2[0])
        return;
    str2[0]++;
    for (; str2[k]; k++) {
        if (check_backticks2(str2, k, last))
            break;
    }
    *i += k;
    create_cmd(var, str2);
    choose_cmd_mouli(str2, var);
}
