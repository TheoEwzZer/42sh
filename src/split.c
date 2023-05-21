/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** minishell
*/

#include "mysh.h"

void split2(char *input, size_t *i, size_t *j, char *new)
{
    if (input[*i] == '<' || input[*i] == '>'
    || input[*i] == '|' || input[*i] == '&') {
        new[(*j)++] = ' ';
        new[(*j)++] = input[(*i)++];
        if (input[*i] == '<' || input[*i] == '>'
        || input[*i] == '|' || input[*i] == '&') {
            new[(*j)++] = input[(*i)++];
        }
        new[(*j)++] = ' ';
        return;
    }
    new[(*j)++] = input[(*i)++];
}

char *split(char *input)
{
    char *new = calloc(strlen(input) * 2 + 1, sizeof(char));
    size_t i = 0;
    size_t j = 0;

    if (input[0] == '<' || input[0] == '>'
    || input[0] == '|' || input[0] == '&') {
        new[j++] = input[i++];
        new[j++] = ' ';
    }
    while (input[i])
        split2(input, &i, &j, new);
    return new;
}

char **split_equals(char **input)
{
    char **new = calloc((my_strlen_double(input) * 3), sizeof(char *));
    char *pos = NULL;
    size_t index = 0;
    size_t j = 0;

    for (size_t i = 0; input[i]; i++) {
        pos = strchr(input[i], '=');
        if (pos && strlen(input[i]) != 1) {
            index = strcspn(input[i], "=");
            new[j++] = strndup(input[i], index);
            new[j++] = strdup("=");
            new[j] = strdup(input[i] + index + 1);
        } else {
            new[j] = strdup(input[i]);
        }
        j++;
    }
    return new;
}
