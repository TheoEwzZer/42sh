/*
** EPITECH PROJECT, 2022
** my_str_to_word_array.c
** File description:
** Splits a string into words.
** Separators will all be non-alphanumeric characters.
** The function returns an array in which each cell
** contains the address of a string (representing a word).
** The last cell must be null to terminate the array.
*/

#include "my.h"
#include <stdlib.h>

int my_char_is_space(char c)
{
    if (c == ' ')
        return 0;
    if (c == '\n')
        return 0;
    if (c == '\r')
        return 0;
    if (c == '\t')
        return 0;
    return 1;
}

int check_word_actu(int word_actu, int *count)
{
    if (!word_actu) {
        word_actu = 1;
        *count = *count + 1;
    }
    return word_actu;
}

int word_count(const char *str)
{
    int count = 0;
    int word_actu = 0;
    int len = my_strlen(str);
    for (int i = 0; i < len; i++) {
        if (my_char_is_space(str[i])) {
            word_actu = check_word_actu(word_actu, &count);
        } else {
            word_actu = 0;
        }
    }
    return count;
}

char **my_str_to_word_array(char const *str)
{
    char **str2 = malloc(sizeof(char*) * (word_count(str) + 1));
    int count2 = 0, i = 0, count3 = 0;
    char *str_tmp = malloc(sizeof(char) * (my_strlen(str) + 1));
    my_strcpy(str_tmp, str);
    for (int k = 0; !my_char_is_space(str[k]); k++)
        count3++;
    str_tmp = increment_str1(count3, str_tmp);
    for (int j = count3; j <= my_strlen(str); j++) {
        count2++;
        if (!my_char_is_space(str[j])) {
            str2[i] = malloc(sizeof(char) * count2);
            my_strncpy(str2[i], str_tmp, count2 - 1);
            str2[i][count2 - 1] = 0;
            str_tmp = increment_str2(count2, str_tmp, &j);
            count2 = 0;
            i++;
        }
    }
    str2[word_count(str)] = 0;
    return str2;
}
