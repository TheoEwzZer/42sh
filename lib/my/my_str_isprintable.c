/*
** EPITECH PROJECT, 2022
** my_str_isprintable.c
** File description:
** Returns 1 if the string passed as parameter only
** contains printable characters and 0 otherwise.
*/

int my_strlen(char const *str);

int my_str_isprintable(char const *str)
{
    int len = my_strlen(str);
    for (int i = 0; i < len; i++) {
        if (str[i] < 32 || str[i] == 127) {
            return 0;
        }
    }
    return 1;
}
