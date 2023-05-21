/*
** EPITECH PROJECT, 2022
** my_isneg.c
** File description:
** Displays either N if the integer passed as
** parameter is negative or P, if positive or null
*/

#include "my.h"

int my_isneg(int n)
{
    if (n >= 0) {
        my_putchar('P');
    } else {
        my_putchar('N');
    }
    return 0;
}
