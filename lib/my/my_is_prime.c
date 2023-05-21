/*
** EPITECH PROJECT, 2022
** my_is_prime.c
** File description:
** Returns 1 if the number is prime and 0 if not.
*/

int my_compute_square_root2(int nb)
{
    int square_root = 0;
    for (int i = 1; i * i <= nb; i++) {
        square_root++;
    }
    return square_root;
}

int my_is_prime(int nb)
{
    if (nb <= 1) {
        return 0;
    }
    int square_root = my_compute_square_root2(nb);
    for (int i = 2; i <= square_root; i++) {
        if (nb % i == 0) {
            return 0;
        }
    }
    return 1;
}
