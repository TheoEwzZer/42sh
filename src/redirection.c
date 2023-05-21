/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** minishell
*/

#include "mysh.h"

void redirection_output(char **str, var_t *var, bool overwrite)
{
    int oflag = O_CREAT | O_WRONLY;

    oflag = overwrite ? oflag | O_TRUNC : oflag | O_APPEND;
    var->fd = open(str[var->index + 1], oflag, 0644);
    if (var->fd == -1) {
        var->return_value = EXIT_FAILURE;
        return;
    }
    dup2(var->fd, STDOUT_FILENO);
    close(var->fd);
}

void redirection_input(char **str, var_t *var)
{
    size_t i = var->index + 2;
    size_t j = var->index;

    var->fd = open(str[var->index + 1], O_RDONLY);
    if (var->fd == -1)
        exit(EXIT_FAILURE);
    dup2(var->fd, STDIN_FILENO);
    close(var->fd);
    if (str[var->index + 2] && str[var->index + 3]
    && str[var->index + 4] && !strcmp(str[var->index + 2], ">"))
        i = var->index + 4;
    else
        i = var->index + 2;
    for (; str[i]; i++) {
        str[j] = str[i];
        j++;
    }
    str[j] = NULL;
}

void builtin_redirection(char **str, var_t *var)
{
    bool overwrite = false;
    var->index = get_index_output(str);
    if (var->index > 0) {
        check_ambiguous_output_redirection(str, var);
        if (!strcmp(str[var->index], ">"))
            overwrite = true;
        if (!str[var->index + 1]) {
            write(2, "Missing name for redirect.\n", 27);
            exit(EXIT_FAILURE);
        }
        if (!access(str[var->index + 1], F_OK)
        && access(str[var->index + 1], W_OK) == -1) {
            write(2, str[var->index + 1], strlen(str[var->index + 1]));
            write(2, ": Permission denied.\n", 21);
            exit(EXIT_FAILURE);
        }
    }
    redirection_output(str, var, overwrite);
}

void handle_output_redirection(char **str, var_t *var)
{
    bool overwrite = false;

    var->index = get_index_output(str);
    if (var->index > 0) {
        check_ambiguous_output_redirection(str, var);
        check_error_output_redirection(str, var, &overwrite);
        redirection_output(str, var, overwrite);
    }
}

void handle_input_redirection(char **str, var_t *var)
{
    if (get_index_pipe(str))
        return;
    var->index = get_index_input(str);
    if (var->index > 0) {
        check_ambiguous_input_redirection(str, var);
        if (!str[var->index + 1]) {
            write(2, "Missing name for redirect.\n", 27);
            exit(EXIT_FAILURE);
        } if (access(str[var->index + 1], F_OK) == -1) {
            write(2, str[var->index + 1], strlen(str[var->index + 1]));
            write(2, ": No such file or directory.\n", 29);
            exit(EXIT_FAILURE);
        } if (!access(str[var->index + 1], F_OK)
            && access(str[var->index + 1], W_OK) == -1) {
            write(2, str[var->index + 1], strlen(str[var->index + 1]));
            write(2, ": Permission denied.\n", 21);
            exit(EXIT_FAILURE);
        }
        redirection_input(str, var);
    }
}
