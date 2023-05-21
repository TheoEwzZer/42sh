/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** minishell
*/

#include "mysh.h"

void replace_foreach(var_t *var, char *variable, char *value)
{
    char **array = str_to_word_array(var->input);

    for (size_t i = 0; array[i]; i++) {
        if (array[i][strlen(array[i]) - 1] == '\"')
            array[i][strlen(array[i]) - 1] = '\0';
        if (!strcmp(array[i], variable))
            array[i] = strdup(value);
    }
    var->input = array[0];
    var->input = my_strcat_malloc(var->input, " ");
    for (size_t i = 1; array[i]; i++) {
        var->input = my_strcat_malloc(var->input, array[i]);
        var->input = my_strcat_malloc(var->input, " ");
    }
}

char **find_all_values(char **array)
{
    char **all_values = calloc(my_strlen_double(array), sizeof(char *));
    size_t j = 0;
    size_t last = 0;

    for (size_t i = 2; array[i]; i++) {
        if (!strcmp(array[i], "(") || !strcmp(array[i], ")"))
            continue;
        all_values[j] = array[i];
        all_values[j + 1] = NULL;
        j++;
    }
    if (all_values[0][0] == '(') {
        for (size_t i = 1; all_values[0][i]; i++)
            all_values[0][i - 1] = all_values[0][i];
        all_values[0][strlen(all_values[0]) - 1] = '\0';
    }
    last = my_strlen_double(all_values) - 1;
    if (all_values[last][strlen(all_values[last]) - 1] == ')')
        all_values[last][strlen(all_values[last]) - 1] = '\0';
    return all_values;
}

void foreach_script(var_t *var, FILE *file, char **array)
{
    char **all_commands = calloc(500, sizeof(char *));
    char **all_values = find_all_values(array);
    char *variable = calloc(100, sizeof(char));
    size_t count = 0, len = 0;
    variable[0] = '$';
    for (size_t i = 0; array[1][i]; i++) {
        variable[i + 1] = array[1][i];
        variable[i + 2] = '\0';
    }
    while (getline(&var->input, &len, file) != -1) {
        if (!strcmp(var->input, "end") || !strcmp(var->input, "end\n")) break;
        all_commands[count++] = strdup(var->input);
    }
    for (size_t i = 0; all_values[i]; i++) {
        for (size_t j = 0; all_commands[j]; j++) {
            var->input = strdup(all_commands[j]);
            replace_foreach(var, variable, all_values[i]);
            execute_commands(var);
        }
    }
}

bool handle_error_scripting(char **str, var_t *var, FILE *file, size_t len)
{
    if (access(str[0], X_OK) == -1 && errno == EACCES) {
        write(2, str[0], strlen(str[0]));
        write(2, ": Permission denied.\n", 21);
        var->return_value = EXIT_FAILURE;
        return true;
    }
    if (!file || getline(&var->input, &len, file) == -1
        || strncmp(var->input, "#!/", 3)) {
        if (file && strncmp(var->input, "#!/", 3) && strlen(str[0]) > 0
        && str[0][0] == '.' && str[0][1] == '/')
            return true;
        write(2, str[0], strlen(str[0]));
        write(2, ": Command not found.\n", 21);
        var->return_value = EXIT_FAILURE;
        return true;
    }
    return false;
}

void exec_script(char **str, var_t *var)
{
    FILE *file = fopen(str[0], "r");
    char **array = NULL;
    size_t len = 0;

    if (handle_error_scripting(str, var, file, len))
        return;
    while (getline(&var->input, &len, file) != -1) {
        if (var->input[0] == '#')
            continue;
        array = str_to_word_array(var->input);
        if (!strncmp(var->input, "foreach", 7))
            foreach_script(var, file, array);
        else
            execute_commands(var);
        var->input = NULL;
    }
}
