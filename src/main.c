/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** minishell
*/

#include "mysh.h"

void check_not_found_and_close(char **str, var_t *var)
{
    int status = 0;

    begin_with_pipe(str, var);
    if (!var->pid) {
        handle_input_redirection(str, var);
        handle_output_redirection(str, var);
        handle_pipe(str, var);
        globbing(str, var);
    } else {
        waitpid(var->pid, &status, WUNTRACED | WCONTINUED);
        handle_errors(status, var);
    }
}

void create_cmd(var_t *var, char **str)
{
    size_t len_cmd = 0;

    if (var->actu_path)
        len_cmd = strlen(str[0]) + strlen(var->actu_path) + 2;
    else
        len_cmd = strlen(str[0]) + 2;
    var->cmd = calloc(len_cmd, sizeof(char));
    if (str[0][0] != '.' && str[0][0] != '/') {
        if (var->actu_path)
            var->cmd = strcat(var->cmd, var->actu_path);
        var->cmd = strcat(var->cmd, "/");
    }
    var->cmd = strcat(var->cmd, str[0]);
}

void cmd_mouli(var_t *var)
{
    char **str = create_str(var);
    if (!str[0])
        return;
    if (check_command_not_found(str, var))
        return;
    var->cmd = NULL;
    if (strlen(var->input) <= 1) {
        var->return_value = EXIT_SUCCESS;
        free(str);
        return;
    }
    create_cmd(var, str);
    choose_cmd_mouli(str, var);
    free(str);
}

void free_all(var_t *var)
{
    alias_t *tmp = var->alias;
    variables_t *tmp2 = var->variables;
    free(var->actu_path); free(var->cwd); free(var->old_cwd); free(var->input);
    free(var->path_complete); free(var->term); free(var->set);
    while (var->alias) {
        tmp = var->alias;
        var->alias = var->alias->next;
        free(tmp->alias);
        for (size_t i = 0; tmp->command[i]; i++)
            free(tmp->command[i]);
        free(tmp->command); free(tmp);
    }
    while (var->variables) {
        tmp2 = var->variables;
        var->variables = var->variables->next;
        free(tmp2->variables);
        for (size_t i = 0; tmp2->value[i]; i++)
            free(tmp2->value[i]);
        free(tmp2->value); free(tmp2);
    }
}

int main(int argc, char **argv, char **env)
{
    var_t *var = malloc(sizeof(var_t)); malloc_history(var);
    var->set = malloc(sizeof(set_t));
    (void)argv; check_arg(argc);
    var->return_value = EXIT_SUCCESS; var->modify_env = false;
    var->env = env; var->path = NULL;
    var->alias = NULL; var->variables = NULL; var->actu_path = NULL;
    var->path_complete = NULL; var->term = NULL; var->input = NULL;
    var->old_cwd = strdup(getcwd(NULL, 0));
    found_home_and_path(var);
    found_special_variables(var);
    var->cwd = strdup(getcwd(NULL, 0));
    var->save_fd = dup(STDOUT_FILENO);
    create_variables(var);
    if (!isatty(STDIN_FILENO)) {
        get_input(var);
    } else {
        while (true)
            wait_cmd(env, var);
    } free_all(var);
    return var->return_value;
}
