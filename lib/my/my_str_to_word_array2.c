/*
** EPITECH PROJECT, 2022
** my_str_to_word_array.c
** File description:
** suite
*/

#include "my.h"

char *increment_str1(int count, char *str_tmp)
{
    for (int k = 0; k < count; k++) {
        str_tmp++;
    }
    return str_tmp;
}

int check_end(int end, char *str_tmp)
{
    if (str_tmp[0] == '\0') {
        end = 1;
    }
    return end;
}

char *increment_str2(int count, char *str_tmp, int *j)
{
    int k = 0;
    int end = 0;
    for (k; k < count; k++) {
        if (end == 0) {
            end = check_end(end, str_tmp);
        }
        str_tmp++;
    }
    while (!end && !my_char_is_space(str_tmp[0])) {
        if (str_tmp[0] == '\0') {
            return str_tmp;
        }
        str_tmp++;
        *j = *j + 1;
    }
    return str_tmp;
}
