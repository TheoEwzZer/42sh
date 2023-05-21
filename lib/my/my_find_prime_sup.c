/*
** EPITECH PROJECT, 2022
** my_find_prime_sup.c
** File description:
** Returns the smallest prime number that is greater than,
** or equal to, the number given as a parameter.
*/

int my_compute_square_root2(int nb);

int my_is_prime2(int nb)
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
    return nb;
}

int my_find_prime_sup(int nb)
{
    int verif = 0;
    for (int i = nb; verif == 0; i++) {
        verif = my_is_prime2(i);
    }
    return verif;
}
