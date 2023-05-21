/*
** EPITECH PROJECT, 2022
** my_strdup.c
** File description:
** Allocates memory and copies the string given as argument in it.
*/

#include <stdlib.h>
#include "my.h"

char *my_strdup(char const *src)
{
    int len = my_strlen(src);
    char *str = malloc(sizeof(char) * (len + 1));
    for (int i = 0; i <= len; i++)
        str[i] = '\0';
    my_strcpy(str, src);
    return str;
}
