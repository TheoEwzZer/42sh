/*
** EPITECH PROJECT, 2022
** my_swap.c
** File description:
** Swaps the content of two integers, whose addresses are given as a parameter.
*/

void my_swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void my_swap_char(char **a, char **b)
{
    char *tmp = *a;
    *a = *b;
    *b = tmp;
}
