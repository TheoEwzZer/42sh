/*
** EPITECH PROJECT, 2022
** my_strcmp.c
** File description:
** Reproduce the behavior of the strcmp function.
*/

#include "my.h"

int my_strcmp(char const *s1, char const *s2)
{
    int len_s1 = my_strlen(s1);
    int len_s2 = my_strlen(s2);
    int max = 0;
    if (len_s1 > len_s2)
        max = len_s1;
    else
        max = len_s2;
    for (int i = 0; i < max; i++) {
        if (s1[i] < s2[i])
            return -1;
        if (s1[i] > s2[i])
            return 1;
    }
    return 0;
}

int my_strcmp_ignore_case(char const *s1, char const *s2)
{
    char *s3 = my_strdup(s1);
    char *s4 = my_strdup(s2);
    s3 = my_strlowcase(s3);
    s4 = my_strlowcase(s4);
    int len_s1 = my_strlen(s1);
    int len_s2 = my_strlen(s2);
    int max = 0;
    if (len_s1 > len_s2)
        max = len_s1;
    else
        max = len_s2;
    for (int i = 0; i < max; i++) {
        if (s3[i] < s4[i])
            return -1;
        if (s3[i] > s4[i])
            return 1;
    }
    return 0;
}
