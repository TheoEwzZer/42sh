/*
** EPITECH PROJECT, 2022
** my_putnbr_base.c
** File description:
** Converts and displays a decimal number into a number in a given base.
** The number is given as an int and the base is provided as a string.
** The base contains all the symbols that can be used to print a number
** (for instance, 0123456789 for the decimal base, 01 for the binary base,
** 0123456789ABCDEF for the hexadecimal base).
** The function must deal with negative numbers
*/

#include "my.h"

int my_putnbr_base(unsigned int nbr, char *base, int count)
{
    int len = my_strlen(base);
    int reste = nbr % len;
    int quotient = nbr / len;
    if (quotient != 0) {
        count = my_putnbr_base(quotient, base, count);
    }
    count += my_putchar(base[reste]);
    return count;
}

int my_putnbr_base_long(unsigned long nbr, char *base, int count)
{
    int len = my_strlen(base);
    int reste = nbr % len;
    int quotient = nbr / len;
    if (quotient != 0) {
        count = my_putnbr_base(quotient, base, count);
    }
    count += my_putchar(base[reste]);
    return count;
}
