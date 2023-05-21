/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** minishell
*/

#include "mysh.h"

size_t nb_delim(char *str, char delim)
{
    size_t nb = 0;

    for (size_t i = 0; str[i]; i++) {
        if (str[i] == delim)
            nb++;
    }
    return nb;
}

char **my_str_to_word_delim(char *str, char delimiter)
{
    char **array = calloc(nb_delim(str, delimiter) + 2, sizeof(char *));
    size_t x = 0, y = 0;

    for (size_t i = 0; str[i]; i++) {
        if (str[i] == delimiter) {
            array[x] = calloc(y + 1, sizeof(char));
            strncpy(array[x], str + i - y, y);
            x++;
            y = 0;
        } else {
            y++;
        }
    }
    if (y > 0) {
        array[x] = calloc(y + 1, sizeof(char));
        strncpy(array[x], str + strlen(str) - y, y);
        x++;
    }
    return array;
}

void free_str_array(char **array)
{
    if (!array)
        return;
    for (size_t i = 0; array[i]; i++)
        free(array[i]);
    free(array);
}

void check_where_commands(char **str, var_t *var, char **path, bool *not_found)
{
    char *cmd = NULL;
    char *tmp = NULL;
    unsigned int found = 0;

    for (size_t i = 1; str[i] && !is_a_redirection(str[i][0]); i++) {
        check_alias_where(var, str, i, &found);
        check_builtins_where(str[i], &found);
        if (where_slash(str[i], var)) {
            *not_found = true;
            continue;
        }
        for (size_t j = 0; path[j]; j++) {
            tmp = my_strcat_malloc(path[j], "/");
            cmd = my_strcat_malloc(tmp, str[i]);
            check_access(cmd, &found);
        }
        if (!found)
            *not_found = true;
        found = 0;
    }
}

void builtin_where(char **str, var_t *var)
{
    bool not_found = false;
    char **path_tab = my_str_to_word_delim(var->path_complete, ':');
    int status = 0;

    handle_pipe_where(str, var);
    waitpid(var->pid, &status, WUNTRACED | WCONTINUED);
    for (size_t i = 1; str[i]; i++) {
        if (is_a_redirection(str[i][0])) {
            builtin_redirection(str, var);
            break;
        }
    }
    if (error_where(str, var)) {
        free_str_array(path_tab);
        return;
    }
    check_where_commands(str, var, path_tab, &not_found);
    free_str_array(path_tab);
    var->return_value = (not_found) ? EXIT_FAILURE : EXIT_SUCCESS;
    dup2(var->save_fd, STDOUT_FILENO);
}
