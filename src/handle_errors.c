/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** minishell
*/

#include "mysh.h"

void handle_errors(int status, var_t *var)
{
    int error = WTERMSIG(status);
    if (!WIFSIGNALED(status)) {
        var->return_value = WEXITSTATUS(status);
        return;
    }
    if (error == SIGFPE)
        write(2, "Floating exception", 18);
    else
        write(2, strsignal(error), strlen(strsignal(error)));
    if (WCOREDUMP(status)) {
        write(2, " (core dumped)", 14);
    }
    write(2, "\n", 1);
    var->return_value = status;
    if (WIFEXITED(status))
        var->return_value = WEXITSTATUS(status);
}

int handle_errors_setenv(char **str, var_t *var)
{
    size_t len = my_strlen_double(str), max = 2;
    if (len > 3 && !strcmp(str[2], "=")) len -= 2, max = 3;
    if (len > 3) {
        write(2, "setenv: Too many arguments.\n", 28);
        var->return_value = EXIT_FAILURE; return EXIT_FAILURE;
    } if (len == 1) {
        my_show_word_array(var->env);
        var->return_value = EXIT_SUCCESS; return EXIT_FAILURE;
    } if (str[2] && str[3] && !strcmp(str[2], "=")) {
        write(2, "Illegal variable name.\n", 23);
        var->return_value = EXIT_FAILURE; return EXIT_FAILURE;
    } if (!my_char_isalpha(str[1][0])) {
        write(2, "setenv: Variable name must begin with a letter.\n", 48);
        var->return_value = EXIT_FAILURE; return EXIT_FAILURE;
    } if (!isalphanum(var->input, max)) {
        write(
            2,
            "setenv: Variable name must contain alphanumeric characters.\n",
            60 ); var->return_value = EXIT_FAILURE; return EXIT_FAILURE;
    } return EXIT_SUCCESS;
}

bool is_valid_variable_value(const char *str)
{
    if (!str || str[0] == '\0')
        return false;
    for (size_t i = 0; str[i]; i++) {
        if (!isalnum(str[i]) && str[i] != '_')
            return false;
    }
    return true;
}

int handle_errors_set(char **str, var_t *var)
{
    size_t len = my_strlen_double(str);
    if (len == 4 && !is_valid_variable_value(str[3])) {
        write(2, "Illegal variable name.\n", 23);
        var->return_value = EXIT_FAILURE;
        return EXIT_FAILURE;
    }
    if (len == 3 && !my_char_isalpha(str[2][0])) {
        write(2, "set: Variable name must begin with a letter.\n", 45);
        var->return_value = EXIT_FAILURE;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

void handle_errors_cd(char **str)
{
    struct stat st;
    if (str[2] && strcmp(str[2], "|")) {
        write(2, "cd: Too many arguments.\n", 24);
        exit(EXIT_FAILURE);
    }
    if (stat(str[1], &st) && strcmp(str[1], "-")) {
        write(2, str[1], strlen(str[1]));
        write(2, ": No such file or directory.\n", 29);
        exit(EXIT_FAILURE);
    }
    if (!S_ISDIR(st.st_mode) && strcmp(str[1], "-")) {
        write(2, str[1], strlen(str[1]));
        write(2, ": Not a directory.\n", 19);
        exit(EXIT_FAILURE);
    }
    if (access(str[1], X_OK) && strcmp(str[1], "-")) {
        write(2, str[1], strlen(str[1]));
        write(2, ": Permission denied.\n", 21);
        exit(EXIT_FAILURE);
    }
}
