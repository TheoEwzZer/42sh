/*
** EPITECH PROJECT, 2022
** my_str_isalpha.c
** File description:
** Returns 1 if the string passed as parameter only
** contains alphabetical characters and 0 if the string
** contains another type of character.
*/

int my_strlen(char const *str);

int check_isalpha(int i, char *str)
{
    if (!(str[i] >= 65 && str[i] <= 90) && !(str[i] >= 97 && str[i] <= 122)) {
        return 0;
    }
    return 1;
}

int my_str_isalpha(char *str)
{
    int len = my_strlen(str);
    for (int i = 0; i < len; i++) {
        if (!check_isalpha(i, str)) {
            return 0;
        }
    }
    return 1;
}
