/*
** EPITECH PROJECT, 2022
** my_strncat.c
** File description:
** Concatenates n characters of the src string to the end of the dest string.
*/

int my_strlen(char const *str);

char *my_strncat(char *dest, char const *src, int nb)
{
    int len_dest = my_strlen(dest);
    int len_src = my_strlen(src);
    for (int i = 0; i <= len_src && i < nb; i++) {
        dest[len_dest + i] = src[i];
    }
    return dest;
}
