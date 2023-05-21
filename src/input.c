/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** minishell
*/

#include "mysh.h"

char **create_str(var_t *var)
{
    char **str = NULL;
    char *big = NULL;

    if (var->input[strlen(var->input) - 1] != '\n') {
        big = calloc(strlen(var->input) + 2, sizeof(char));
        big = strcat(big, var->input);
        big = strcat(big, "\n");
        str = str_to_word_array(big);
        free(big);
    } else {
        str = str_to_word_array(var->input);
    }
    replace_with_alias(var, &str);
    replace_with_variables(var, &str);
    return str;
}

void get_input(var_t *var)
{
    size_t len = 0;

    var->input = NULL;
    while (getline(&var->input, &len, stdin) != -1) {
        execute_commands(var);
        var->input = NULL;
    }
}

void execute_commands(var_t *var)
{
    char *save_ptr_semicolon = NULL;
    char *semicolon_token = NULL;

    semicolon_token = strtok_r(var->input, ";", &save_ptr_semicolon);
    while (semicolon_token) {
        execute_or_tokens(var, semicolon_token);
        semicolon_token = strtok_r(NULL, ";", &save_ptr_semicolon);
    }
}

void execute_or_tokens(var_t *var, char *semicolon_token)
{
    char *save_ptr_or = NULL;
    char *or_token = NULL;
    int status = 0;

    or_token = my_strtok_r(semicolon_token, "||", &save_ptr_or);
    while (or_token) {
        execute_and_tokens(var, or_token, &status);
        or_token = my_strtok_r(NULL, "||", &save_ptr_or);
        if (status == 0)
            break;
    }
}

void execute_and_tokens(var_t *var, char *or_token, int *status)
{
    char *save_ptr_and = NULL;
    char *and_token = NULL;

    and_token = my_strtok_r(or_token, "&&", &save_ptr_and);
    while (and_token) {
        var->input = split(and_token);
        execute_repeat(var);
        (*status) = var->return_value;
        and_token = my_strtok_r(NULL, "&&", &save_ptr_and);
        var->input = NULL;
        if (*status != 0)
            break;
    }
}
