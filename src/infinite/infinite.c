/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** minishell
*/

#include "mysh.h"

void check(char **str, var_t *var)
{
    int status = 0;
    var->pid = fork();
    if (var->pid == -1)
        exit(EXIT_FAILURE);
    if (!var->pid) {
        globbing(str, var);
    } else {
        waitpid(var->pid, &status, WUNTRACED | WCONTINUED);
        handle_errors(status, var);
    }
}

void wait_cmd2(char **str, var_t *var)
{
    if (str[0][0] != '.' && str[0][0] != '/') {
        if (var->actu_path)
            var->cmd = strcat(var->cmd, var->actu_path);
        var->cmd = strcat(var->cmd, "/");
    }
    var->cmd = strcat(var->cmd, str[0]);
    choose_cmd(str, var);
    free(var->cmd);
    var->cmd = NULL;
    free(var->input);
    var->input = NULL;
    for (size_t i = 1; str[i]; i++)
        free(str[i]);
    free(str);
}

void wait_cmd(char **env, var_t *var)
{
    char **str = NULL;
    size_t len_cmd = 0, len = 0; var->cmd = NULL; var->input = NULL;
    signal_handling(); set_prompt(var);
    if (getline(&var->input, &len, stdin) == -1) exit(EXIT_FAILURE);
    if (strlen(var->input) <= 1) {
        free(var->input);
        var->input = NULL;
        wait_cmd(env, var);
        return;
    }
    str = my_str_to_word_array(var->input);
    save_history(var); var->old_cmd = var->input;
    replace_with_alias(var, &str); replace_with_variables(var, &str);
    if (str[0] && var->actu_path && var->path) {
        len_cmd = strlen(str[0]) + strlen(var->actu_path) + 2;
        var->cmd = calloc(len_cmd, sizeof(char));
    } if (!var->cmd || !var->path) {
        execvp(str[0], str); return;
    }
    wait_cmd2(str, var);
}
