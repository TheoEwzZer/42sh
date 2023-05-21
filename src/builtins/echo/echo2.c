/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** minishell
*/

#include "mysh.h"

void write_token2(char *token, size_t i, size_t nbr)
{
    if (token[i] == '\\' && token[i + 1] == '\"') {
        if (token[i + 2] != '\0')
            write(1, &token[i + 1], 1);
        if (token[i + 2] == '\0' && nbr % 2 == 0)
            write(1, &token[i + 1], 1);
    }
}

char **loop_echo(char **str, size_t j)
{
    for (size_t i = 0; str[j][i]; i++) {
        if (str[j][i] == '\"' && str[j][i + 1] == '\"') {
            str[j][i] = str[j][i + 2];
            str[j] = move_my_str(str[j], i + 2);
        }
    }
    return str;
}

bool write_str2(char **str, var_t *var, size_t *i, bool *line_break)
{
    if (!strncmp(str[*i], "$", 1)) {
        check_all_variable(str, var, i);
        return true;
    }
    if (!strncmp(str[*i], "`", 1)) {
        check_backticks(str, var, i);
        if (line_break && *line_break)
            *line_break = false;
        return true;
    }
    return false;
}

void write_str(char **str, var_t *var, bool *line_break)
{
    char *ret_str = calloc(4, sizeof(char));
    int len = 0;

    for (size_t i = 1; str[i]; i++) {
        if (!strcmp(str[i], "$?")) {
            len = snprintf(ret_str, 4, "%d", var->return_value);
            write(1, ret_str, (size_t)len);
            continue;
        }
        if (write_str2(str, var, &i, line_break))
            continue;
        write_token(str[i]);
        if (str[i + 1])
            write(1, " ", 1);
    }
    free(ret_str);
}
