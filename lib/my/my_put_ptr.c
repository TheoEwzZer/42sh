/*
** EPITECH PROJECT, 2022
** my_put_ptr.c
** File description:
** my_put_ptr
*/

#include "my.h"

int my_put_ptr(unsigned int nbr, int count)
{
    char *base = "0123456789abcdef";
    int reste = nbr % 16;
    int quotient = nbr / 16;
    if (quotient != 0)
        count = my_put_ptr(quotient, count);
    if (count == 2)
        my_putstr("0x");
    count += my_putchar(base[reste]);
    return count;
}
