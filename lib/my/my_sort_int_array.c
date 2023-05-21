/*
** EPITECH PROJECT, 2022
** my_sort_int_array.c
** File description:
** Sorts an integer array in ascending order, given a
** pointer to the first element of the array and its size.
*/

void my_swap(int *a, int *b);

void my_sort_int_array(int *array, int size)
{
    int j = 0;
    for (int i = 0; j < size - 1; i++) {
        if (array[j] > array[j + 1]) {
            my_swap(&array[j], &array[j + 1]);
            j = 0;
        } else {
            j++;
        }
    }
}
