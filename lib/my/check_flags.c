/*
** EPITECH PROJECT, 2022
** check_flags.c
** File description:
** check_flags
*/

#include <stdarg.h>
#include "my.h"

int check_flags(char c)
{
    switch (c) {
    case 's':
    case 'd':
    case 'i':
    case 'b':
    case 'c':
    case 'S':
    case 'x':
    case 'X':
    case '%':
    case 'o':
    case 'p':
    case 'u':
    case 'l':
        return 1;
    default:
        return 0;
    }
}

int check_flags2(char c)
{
    switch (c) {
    case '+':
    case '-':
    case '#':
    case '0':
        return 1;
    default:
        return 0;
    }
}
