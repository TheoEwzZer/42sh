/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** minishell
*/

#include "mysh.h"

void builtin_env(char **str, var_t *var)
{
    int status = 0;
    size_t len_cmd = 0;

    handle_pipe_env(str, var);
    waitpid(var->pid, &status, WUNTRACED | WCONTINUED);
    if (str[1]) {
        builtin_redirection(str, var);
        free(var->cmd);
        len_cmd = strlen(str[1]) + 6;
        var->cmd = calloc(len_cmd, sizeof(char));
        var->cmd = strcat(var->cmd, "/bin/");
        var->cmd = strcat(var->cmd, str[1]);
    }
    my_show_word_array(var->env);
    dup2(var->save_fd, STDOUT_FILENO);
}
