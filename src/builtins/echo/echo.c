/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** minishell
*/

#include "mysh.h"

void write_token(char *token)
{
    size_t nbr = 0, len = strlen(token);
    for (size_t i = 0; i < len; i++) {
        write_token2(token, i, nbr);
        if (token[i] == '\"' && (i == 0 || token[i - 1] == '\\'))
            nbr++;
        if ((token[i] == '\"' || token[i] == '\'')
        && (i == 0 || token[i - 1] != '\\'))
            continue;
        if (token[i] == '\\') {
            i++;
            switch (token[i]) {
                case 'n':
                    write(1, "\n", 1); break;
                case 't':
                    write(1, "\t", 1); break;
                default: break;
            }
        } else
            write(1, &token[i], 1);
    }
}

void check_all_variable2(variables_t *current_var, var_t *var)
{
    size_t len = 0;

    if (!current_var->value[0])
        return;
    if (!strcmp(current_var->value[0], "echo")) {
        write(1, "echo", 4);
        write(1, " ", 1);
        write_str(current_var->value, var, NULL);
        return;
    }
    for (size_t j = 0; current_var->value[j]; j++) {
        if (j != 0)
            write(1, " ", 1);
        len = strlen(current_var->value[j]);
        write(1, current_var->value[j], len);
    }
}

void check_all_variable(char **str, var_t *var, size_t *i)
{
    variables_t *current_var = NULL;

    str[*i]++;
    current_var = var->variables;
    while (current_var) {
        if (!strcmp(str[*i], current_var->variables)) {
            check_all_variable2(current_var, var);
            return;
        }
        current_var = current_var->next;
    }
    write(1, str[*i], strlen(str[*i]));
    write(1, ": Undefined variable.\n", 22);
    var->return_value = EXIT_FAILURE;
    exit(EXIT_FAILURE);
}

void builtin_echo(char **str, var_t *var)
{
    bool line_break = true;

    for (size_t j = 1; str[j]; j++)
        str = loop_echo(str, j);
    if (!str[1]) {
        write(1, "\n", 1);
        var->return_value = EXIT_SUCCESS;
        return;
    }
    if (!strcmp(str[1], "-n")) {
        line_break = false;
        str++;
    }
    write_str(str, var, &line_break);
    if (line_break)
        write(1, "\n", 1);
    var->return_value = EXIT_SUCCESS;
}
