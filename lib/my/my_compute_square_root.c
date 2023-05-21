/*
** EPITECH PROJECT, 2022
** my_compute_square_root.c
** File description:
** Returns the square root (if it is a whole number)
** of the number given as argument.
** If the square root is not a whole number,
** the function should return 0.
*/

int my_compute_square_root(int nb)
{
    for (int i = 1; i <= nb; i++) {
        if (i * i == nb) {
            return i;
        }
    }
    return 0;
}
