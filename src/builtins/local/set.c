/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** minishell
*/

#include "mysh.h"

void builtin_set2(char **str, var_t *var, char *str2)
{
    char *variable = NULL;
    size_t argc = 0;
    char **value = NULL;

    variable = strdup(str[var->set->i - 2]);
    for (; str[var->set->i]; var->set->i++) {
        argc++;
        value = realloc(value, sizeof(char *) * argc);
        value[argc - 1] = strdup(str[var->set->i]);
    }
    argc++;
    value = realloc(value, sizeof(char *) * argc);
    value[argc - 1] = NULL;
    add_variables(var, variable, value);
    str[var->set->j + 1] = str2;
    str += var->set->i - 1;
    builtin_set(str, var, false);
}

void builtin_set(char **str, var_t *var, bool first)
{
    char *str2 = NULL;
    char **str3 = split_equals(str);
    size_t i = 0; var->set->i = 3; var->set->j = 3;

    if (handle_errors_set(str, var)) return;
    for (; str3[i]; i++);
    if (!str3[1] && first) {
        print_variables(var);
        return;
    } if (i < 4)
        return;
    str2 = str3[var->set->i + 1];
    if (str3[1][0] == '-') {
        var->set->i++;
        var->set->j++;
    } if (!str3[var->set->i - 1] || str3[var->set->i - 1][0] != '=')
        return;
    if (str3[var->set->i][0] != '"')
        str3[var->set->i + 1] = NULL;
    builtin_set2(str3, var, str2);
}

char **get_variables(var_t *var, char *value, size_t *argc)
{
    variables_t *current_var = NULL;

    value++;
    if (!var->variables)
        return NULL;
    current_var = var->variables;
    while (current_var) {
        if (!strcmp(value, current_var->variables)) {
            (*argc) = current_var->argc;
            return current_var->value;
        }
        current_var = current_var->next;
    }
    return NULL;
}

void expand_variables(char ***str_ptr, char **value, size_t i, size_t argc)
{
    char **str = *str_ptr;

    str = realloc(str, sizeof(char *) * (i + argc + 1));
    (*str_ptr) = str;
    for (size_t j = 1; j < argc; j++)
        str[i + j] = strdup(value[j]);
    str[i + argc] = NULL;
}

void print_variables(var_t *var)
{
    variables_t *current_var = NULL;
    size_t len = 0;

    if (!var->variables) {
        write(2, "No variables.\n", 14);
        return;
    }
    current_var = var->variables;
    while (current_var) {
        write(1, current_var->variables, strlen(current_var->variables));
        write(1, "\t", 1);
        write(1, current_var->value[0], strlen(current_var->value[0]));
        for (size_t i = 1; i < current_var->argc; i++) {
            write(1, " ", 1);
            len = strlen(current_var->value[i]);
            write(1, current_var->value[i], len);
        }
        write(1, "\n", 1);
        current_var = current_var->next;
    }
}
