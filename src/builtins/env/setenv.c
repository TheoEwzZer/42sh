/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** minishell
*/

#include "mysh.h"

char **strdup_double(char **src)
{
    size_t i = 0;
    size_t len = my_strlen_double(src);
    char **str = calloc(len + 2, sizeof(char *));

    for (i = 0; src[i]; i++)
        str[i] = strdup(src[i]);
    return str;
}

char **my_strdup_double(char **src, char *env_to_set)
{
    size_t i = 0;
    size_t len = my_strlen_double(src);
    char **str = calloc(len + 2, sizeof(char *));

    for (i = 0; src[i]; i++)
        str[i] = strdup(src[i]);
    for (size_t j = i; j < i + 1; j++)
        str[j] = env_to_set;
    return str;
}

char *create_new_env(char **str)
{
    char *new_env = NULL;
    size_t len = 0;

    if (str[2]) {
        len = strlen(str[1]) + 1 + strlen(str[2]) + 1;
        new_env = calloc(len, sizeof(char));
        new_env = strcat(new_env, str[1]);
        new_env = strcat(new_env, "=");
        new_env = strcat(new_env, str[2]);
    } else {
        len = strlen(str[1]) + 1 + 1;
        new_env = calloc(len, sizeof(char));
        new_env = strcat(new_env, str[1]);
        new_env = strcat(new_env, "=");
    }
    return new_env;
}

bool isalphanum(char *str, size_t max)
{
    unsigned int space = 0;
    for (size_t i = 0; str[i] && space < max; i++) {
        if (isalnum(str[i]))
            continue;
        if (str[i] == ' ') {
            space++;
            continue;
        }
        if (str[i] == '\n')
            continue;
        if (str[i] == '/')
            continue;
        return false;
    }
    return true;
}

void builtin_setenv(char **str, var_t *var)
{
    bool found = false;
    char *new_env = NULL;
    if (handle_errors_setenv(str, var))
        return;
    var->modify_env = true;
    new_env = create_new_env(str);
    for (size_t i = 0; var->env[i]; i++) {
        if (!strncmp(var->env[i], new_env, strlen(str[1]) + 1)) {
            var->env[i] = new_env; found = true;
            found_home_and_path(var);
            break;
        }
    }
    var->env = found ? var->env : my_strdup_double(var->env, new_env);
}
