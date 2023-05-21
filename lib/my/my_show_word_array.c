/*
** EPITECH PROJECT, 2022
** my_show_word_array.c
** File description:
** Displays the content of an array of words
*/

#include "my.h"
#include <sys/stat.h>
#include <unistd.h>

void my_show_word_array(char *const *tab)
{
    for (int i = 0; tab[i] != 0; i++) {
        write(1, tab[i], my_strlen(tab[i]));
        write(1, "\n", 1);
    }
}
