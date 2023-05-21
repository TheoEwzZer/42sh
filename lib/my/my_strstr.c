/*
** EPITECH PROJECT, 2022
** my_strstr.c
** File description:
** Reproduce the behavior of the strstr function.
*/

int my_strlen(char const *str);
int my_strncmp(char const *s1, char const *s2, int n);

#include <stddef.h>

char *my_strstr(char *str, char const *to_find)
{
    int len_str = my_strlen(str);
    int len_to_find = my_strlen(to_find);
    for (int i = 0; i < len_str; i++) {
        if (my_strncmp(str, to_find, len_to_find) == 0) {
            return str;
        }
        str++;
    }
    return NULL;
}
