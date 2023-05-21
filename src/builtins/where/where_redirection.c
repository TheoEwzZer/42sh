/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** minishell
*/

#include "mysh.h"

void execute_first_command_where(char **str, var_t *var)
{
    pid_t pid = 0;
    bool not_found = false;
    char **path_tab = my_str_to_word_delim(var->path_complete, ':');

    pipe(var->pipe_descriptor);
    pid = fork();
    if (!pid) {
        close(var->pipe_descriptor[0]);
        dup2(var->pipe_descriptor[1], STDOUT_FILENO);
        close(var->pipe_descriptor[1]);
        if (error_where(str, var)) {
            free_str_array(path_tab);
            return;
        }
        check_where_commands(str, var, path_tab, &not_found);
        free_str_array(path_tab);
        var->return_value = (not_found) ? EXIT_FAILURE : EXIT_SUCCESS;
        exit(EXIT_SUCCESS);
    }
    close(var->pipe_descriptor[1]);
}

void handle_pipe_where(char **str, var_t *var)
{
    char **commands = NULL;
    int status = 0;
    pid_t pid1 = 0, pid2 = 0;
    var->pipe_descriptor = calloc(2, sizeof(int));
    var->index = get_index_pipe(str);
    if (var->index > 0) {
        check_ambiguous_input_redirection(str, var);
        if (!str[var->index + 1] || !strcmp(str[var->index + 1], "|")) {
            write(2, "Invalid null command.\n", 22); exit(EXIT_FAILURE);
        }
        if (!(pid1 = fork())) {
            str[var->index] = NULL;
            execute_first_command_where(str, var);
            commands = get_commands(var, str); pid2 = fork();
            execute_second_command(commands, var, pid2, &status);
            close(var->pipe_descriptor[0]); close(var->pipe_descriptor[1]);
            waitpid(pid2, &status, WUNTRACED | WCONTINUED);
            handle_errors(status, var); exit(var->return_value);
        }
    }
}
