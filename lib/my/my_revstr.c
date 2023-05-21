/*
** EPITECH PROJECT, 2022
** my_revstr.c
** File description:
** Reverses a string.
*/

int my_strlen(char const *str);

int middle(char *str)
{
    int len = my_strlen(str);
    if (len % 2 == 0) {
        return len / 2;
    } else {
        return len / 2 + 1;
    }
}

int my_swapstr(char *a, char *b)
{
    char tmp = *a;
    *a = *b;
    *b = tmp;
    return 0;
}

char *my_revstr(char *str)
{
    int j = my_strlen(str)-1;
    for (int i = 0; i < middle(str); i++) {
        my_swapstr(&str[i], &str[j]);
        j--;
    }
    return str;
}
