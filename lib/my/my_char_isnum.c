/*
** EPITECH PROJECT, 2022
** my_char_isnum.c
** File description:
** Returns 1 if the char passed as
** parameter is a digit and 0 otherwise.
*/

int my_char_isnum(char str)
{
    if (str < 48 || str > 57) {
        return 0;
    }
    return 1;
}
