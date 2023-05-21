/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** minishell
*/

#include "mysh.h"

int check_good_number(char **str)
{
    for (size_t i = 0; str[1][i]; i++) {
        if (str[1][i] < '0' || str[1][i] > '9') {
            write(1, "repeat: Badly formed number.\n", 29);
            return 1;
        }
    }
    return 0;
}

bool check_wrong_path(var_t *var, char **str)
{
    if (!var->path || !var->actu_path) {
        execvp(str[0], str);
        return true;
    }
    return false;
}

void execute_repeat(var_t *var)
{
    char **str = create_str(var); int i = 0, nb = 0;
    if (!str || !str[0] || check_wrong_path(var, str)) return;
    if (strcmp(str[0], "repeat")) {
        cmd_mouli(var); return;
    } if (!str[1] || !str[2]) {
        write(1, "repeat: Too few arguments.\n", 27);
        var->return_value = EXIT_FAILURE; return;
    }
    if (check_good_number(str)) {
        var->return_value = EXIT_FAILURE; return;
    } nb = atoi(str[1]);
    for (i = 0; i < nb; i++) {
        free(var->input); var->input = strdup(str[2]);
        for (size_t j = 3; str[j]; j++) {
            var->input = my_strcat_malloc(var->input, "  ");
            var->input = my_strcat_malloc(var->input, str[j]);
        }
        cmd_mouli(var);
    }
    free(var->input); free(str);
}
