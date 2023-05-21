/*
** EPITECH PROJECT, 2022
** my_strcat.c
** File description:
** Concatenates two strings.
*/

int my_strlen(char const *str);

char *my_strcat(char *dest, const char *src)
{
    int len_dest = my_strlen(dest);
    int len_src = my_strlen(src);
    for (int i = 0; i <= len_src; i++) {
        dest[len_dest + i] = src[i];
    }
    return dest;
}
