/*
** EPITECH PROJECT, 2022
** my_strcapitalize.c
** File description:
** Capitalizes the first letter of each word.
*/

int my_strlen(char const *str);

void check_separator_upper(int i, char *str)
{
    if (str[i - 1] == ' ' || str[i - 1] == '+' || str[i - 1] == '-') {
        str[i] -= 32;
    }
}

void check_separator_lower(int i, char *str)
{
    if (str[i - 1] != ' ' && str[i - 1] != '+' && str[i - 1] != '-') {
        str[i] += 32;
    }
}

char *my_strcapitalize(char *str)
{
    int len = my_strlen(str);
    if (str[0] >= 97 && str[0] <= 122) {
        str[0] -= 32;
    }
    for (int i = 1; i <= len; i++) {
        if (str[i] >= 97 && str[i] <= 122) {
            check_separator_upper(i, str);
        }
        if (str[i] >= 65 && str[i] <= 90) {
            check_separator_lower(i, str);
        }
    }
    return str;
}
