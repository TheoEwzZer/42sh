/*
** EPITECH PROJECT, 2022
** my_strlen.c
** File description:
** Counts and returns the number of characters
** found in the string passed as parameter.
*/

unsigned int my_strlen(char const *str)
{
    unsigned int count = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        count++;
    }
    return count;
}

unsigned int my_strlen_double(char *const *str)
{
    unsigned int count = 0;
    for (int i = 0; str[i]; i++) {
        count++;
    }
    return count;
}
