/*
** EPITECH PROJECT, 2022
** my_showstr.c
** File description:
** Prints a string and returns 0.
** If this string contains non-printable characters,
** they must be printed hexadecimally (in lowercase letters)
** with a backslash before the given value.
*/

#include "my.h"

void hexa(int i, char *str)
{
    my_putchar('\\');
    if (str[i] < 16) {
        my_putchar('0');
    }
    my_putnbr_base(str[i], "0123456789abcdef", 0);
}

int my_showstr(char *str)
{
    for (int i = 0; str[i]; i++) {
        if (str[i] >= 32 && str[i] != 127) {
            my_putchar(str[i]);
        } else {
            hexa(i, str);
        }
    }
    return 0;
}
