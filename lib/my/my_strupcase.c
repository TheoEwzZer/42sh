/*
** EPITECH PROJECT, 2022
** my_strupcase.c
** File description:
** Puts every letter of every word in it in uppercase
*/

int my_strlen(char const *str);

char *my_strupcase(char *str)
{
    int len = my_strlen(str);
    for (int i = 0; i < len; i++) {
        if (str[i] >= 97 && str[i] <= 122) {
            str[i] -= 32;
        }
    }
    return str;
}
