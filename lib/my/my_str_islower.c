/*
** EPITECH PROJECT, 2022
** my_str_islower.c
** File description:
** Returns 1 if the string passed as parameter only contains
** lowercase alphabetical characters and 0 otherwise.
*/

int my_strlen(char const *str);

int my_str_islower(char const *str)
{
    int len = my_strlen(str);
    for (int i = 0; i < len; i++) {
        if (str[i] < 97 || str[i] > 122) {
            return 0;
        }
    }
    return 1;
}
