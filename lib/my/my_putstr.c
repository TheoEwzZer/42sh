/*
** EPITECH PROJECT, 2022
** my_putstr.c
** File description:
** Displays, one-by-one, the characters of a string.
** The address of the string’s first character will be
** found in the pointer passed as a parameter to the function.
*/

#include "my.h"

int my_putstr(char const *str)
{
    int count = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        count += my_putchar(str[i]);
    }
    return count;
}
