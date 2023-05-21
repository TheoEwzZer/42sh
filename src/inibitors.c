/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** inibitors
*/

#include "mysh.h"

char **move_my_tab(char **str, size_t i)
{
    for (; str[i + 1]; i++)
        str[i + 1] = str[i + 2];
    return str;
}

char *move_my_str(char *str, size_t j)
{
    size_t x = 0;
    size_t x_2 = 0;
    char *str_cp = NULL;
    size_t len_str = 0;

    len_str = strlen(str);
    str_cp = calloc(len_str + 1, sizeof(char));
    for (; str[x]; x++, x_2++) {
        if (x == j)
            x_2++;
        str_cp[x] = str[x_2];
    }
    str_cp[x] = '\0';
    return str_cp;
}

char **condition_inibitor_bis(char **str, size_t i, size_t j)
{
    if (str[i][j] == '\\' && str[i][j + 1]) {
        str[i][j] = str[i][j + 1];
        str[i] = move_my_str(str[i], j);
        puts("nul");
        return str;
    }
    if (str[i][j] == '\\' && !str[i][j + 1] && str[i + 1]) {
        str[i] = my_strcat_malloc(str[i], str[i + 1]);
        str[i][j] = ' ';
        str = move_my_tab(str, i);
        return str;
    }
    if (str[i][j] == '\\' && !str[i][j + 1] && !str[i + 1]){
        str[i][j] = ' ';
    }return str;
}

char **condition_inibitor(char **str, size_t i, size_t j)
{
    if (my_strcmp(str[0], "set") == 0 && str[i][j] == '\\'){
        str[i] = move_my_str(str[i], j);
        return str;
    }
    if (str[i][j] == '\\' && str[i][j + 1] == 'n')
        return str;
    if (str[i][j] == '\\' && str[i][j + 1] == 't'){
        return str;
    }
    if (str[i][j] == '\\' && i == 0 && str[i][j + 1] == '\0'){
        str[i][j + 1] = '\\';
        str[i] = move_my_str(str[i], j);
        return str;
    }
    str = condition_inibitor_bis(str, i, j);
    return str;
}

char **inibitors(char **str)
{
    size_t i = 0;
    size_t j = 0;

    if (str[0]){
        if (!strcmp(str[0], "echo")){
            return str;
        }
    }
    for (; str[i]; i++, j = 0) {
        for (; str[i][j]; j++)
            str = condition_inibitor(str, i, j);
    }
    return str;
}
