/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** minishell
*/

#include "mysh.h"

bool check_builtins_which(char *str)
{
    char const *builtins[14] = {"cd", "echo", "setenv", "unsetenv", "where",
    "which", "exit", "alias", "unalias", "repeat", "history", "set",
    "unset", NULL};

    for (size_t i = 0; builtins[i]; i++) {
        if (!strcmp(str, builtins[i])) {
            write(1, str, strlen(str));
            write(1, ": shell built-in command.\n", 26);
            return true;
        }
    }
    return false;
}

bool check_builtin(char *str, var_t *var)
{
    char **path_tab = my_str_to_word_delim(var->path_complete, ':');
    char *cmd = NULL;
    char *tmp = NULL;
    unsigned int found = 0;

    if (check_builtins_which(str))
        return true;
    for (size_t j = 0; path_tab[j]; j++) {
        tmp = my_strcat_malloc(path_tab[j], "/");
        cmd = my_strcat_malloc(tmp, str);
        check_access(cmd, &found);
        if (found > 0)
            break;
    }
    for (size_t i = 0; path_tab[i]; i++)
        free(path_tab[i]);
    free(path_tab);
    free(tmp);
    free(cmd);
    return (found > 0) ? true : false;
}

void which_loop(char **str, var_t *var, char **alias, size_t i)
{
    size_t argc = 0;

    alias = get_alias(var, str[i], &argc);
    if (alias) {
        write(1, str[i], strlen(str[i]));
        write(1, ": \t aliased to", 14);
        for (size_t j = 0; alias[j]; j++) {
            write(1, " ", 1);
            write(1, alias[j], strlen(alias[j]));
        }
        write(1, "\n", 1);
    } else if (!check_builtin(str[i], var)) {
        write(1, str[i], strlen(str[i]));
        write(1, ": Command not found.\n", 21);
        var->return_value = EXIT_FAILURE;
    }
}

void builtin_which(char **str, var_t *var)
{
    char **alias = NULL;
    int status = 0;

    handle_pipe_which(str, var);
    waitpid(var->pid, &status, WUNTRACED | WCONTINUED);
    var->return_value = EXIT_SUCCESS;
    if (!str[1]) {
        write(1, "which: Too few arguments.\n", 26);
        var->return_value = EXIT_FAILURE;
        return;
    }
    for (size_t i = 1; str[i]; i++) {
        if (is_a_redirection(str[i][0])) {
            builtin_redirection(str, var);
            break;
        }
    }
    for (size_t i = 1; str[i] && !is_a_redirection(str[i][0]); i++)
        which_loop(str, var, alias, i);
    dup2(var->save_fd, STDOUT_FILENO);
}
