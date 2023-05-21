/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** minishell
*/

#include "mysh.h"

void builtin_foreach(char **str, var_t *var)
{
    char **all_commands = malloc(sizeof(char *) * 500), **all_values = NULL;
    char *variable = malloc(sizeof(char) * 100);
    size_t len = 0, count = 0;
    if (!str[1] || !str[2]) {
        write(2, "foreach: Too few arguments.\n", 28); var->return_value = 1;
        return;
    } all_values = find_all_values(str);
    variable[0] = '$';
    for (size_t i = 0; str[1][i]; i++) {
        variable[i + 1] = str[1][i]; variable[i + 2] = '\0';
    } while (getline(&var->input, &len, stdin) != -1) {
        if (!strcmp(var->input, "end") || !strcmp(var->input, "end\n")) break;
        all_commands[count++] = strdup(var->input);
    } for (size_t i = 0; all_values[i]; i++){
        for (size_t j = 0; all_commands[j]; j++){
            var->input = strdup(all_commands[j]);
            replace_foreach(var, variable, all_values[i]);
            execute_commands(var);
        }
    } var->return_value = 0;
}
