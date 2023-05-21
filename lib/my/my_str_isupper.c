/*
** EPITECH PROJECT, 2022
** my_str_isupper.c
** File description:
** Returns 1 if the string passed as parameter only contains
** uppercase alphabetical characters and 0 otherwise.
*/

int my_strlen(char const *str);

int my_str_isupper(char const *str)
{
    int len = my_strlen(str);
    for (int i = 0; i < len; i++) {
        if (str[i] < 65 || str[i] > 90) {
            return 0;
        }
    }
    return 1;
}
