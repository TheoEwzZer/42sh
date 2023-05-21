/*
** EPITECH PROJECT, 2023
** history1.c
** File description:
** history1.c
*/
#include "mysh.h"

void malloc_history(var_t *var)
{
    var->hist_value = 0;
    var->history = calloc(4096, sizeof(char *));
    var->history_hour = calloc(4096, sizeof(int));
    var->history_mins = calloc(4096, sizeof(int));
    var->hist_count = calloc(4096, sizeof(int));
}

void builtin_history(var_t *var)
{
    for (size_t c = 0; c != var->hist_value; c++) {
        var->hist_count[c] = c;
        number_condition((int)c);
        my_put_nbr((long)c, 0);
        write(1, "  ", 2);
        my_put_nbr(var->history_hour[c], 0);
        write(1, ":", 1);
        my_put_nbr(var->history_mins[c], 0);
        input_condition(var->history_hour[c]);
        write(1, var->history[c], strlen(var->history[c]));
        if (var->history[c][strlen(var->history[c]) - 1] != '\n')
            write(1, "\n", 1);
    }
}

void save_history(var_t *var)
{
    char *string = calloc(strlen(var->input) + 1, sizeof(char));
    time_t timestamp;
    struct tm *now;

    strcpy(string, var->input);
    timestamp = time(NULL);
    now = localtime(&timestamp);
    var->history_hour[var->hist_value] = now->tm_hour;
    var->history_mins[var->hist_value] = now->tm_min;
    if (!strncmp(string, "!!", 2) && var->hist_value > 0)
        var->history[var->hist_value] = var->history[var->hist_value - 1];
    else
        var->history[var->hist_value] = string;
    var->hist_value = var->hist_value + 1;
    var->hist_save = var->hist_value;
}

char *choose_command_history(var_t *var, char **str)
{
    int save = 0;
    char *string = calloc(4096, sizeof(char));

    string = delete_exclamation(str[0], 1);
    save = atoi(string);
    return var->history[save];
}
