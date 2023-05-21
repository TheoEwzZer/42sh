/*
** EPITECH PROJECT, 2022
** before.c
** File description:
** before.c
*/

#include <stdlib.h>
#include "my.h"

int zero_before(char *array, int count)
{
    if (my_strlen(array) == 2)
        count += my_putchar('0');
    if (my_strlen(array) == 1)
        count += my_putstr("00");
    return count;
}

int zero_before_zero(char *array, int count)
{
    if (my_strlen(array) == 2)
        count += 1;
    if (my_strlen(array) == 1)
        count += 2;
    return count;
}
