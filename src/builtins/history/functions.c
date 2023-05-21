/*
** EPITECH PROJECT, 2023
** functions.c
** File description:
** functions
*/
#include "mysh.h"

void number_condition(int c)
{
    if (c <= 9)
        write(1, "     ", 5);
    if (c >= 10 && c <= 99)
        write(1, "    ", 4);
    if (c >= 100 && c <= 999)
        write(1, "   ", 3);
    if (c >= 1000 && c <= 9999)
        write(1, "  ", 2);
    if (c >= 10000 && c <= 99999)
        write(1, " ", 1);
}

void input_condition(int stock)
{
    if (stock <= 9)
        write(1, "    ", 4);
    else
        write(1, "   ", 3);
}

char *delete_exclamation(char *str, int nb)
{
    char *str_return = calloc(strlen(str), sizeof(char));

    for (; str[nb]; nb++)
        str_return[nb] = str[nb];
    return str_return;
}
