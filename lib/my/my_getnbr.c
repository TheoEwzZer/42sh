/*
** EPITECH PROJECT, 2022
** my_getnbr.c
** File description:
** Returns a number, sent to the function as a string.
*/

int my_strlen(char const *str);

long power10(int len)
{
    long r = 1;
    for (long i = 0; i < len; i++) {
        r *= 10;
    }
    return r;
}

int int_at(int index, char *tab)
{
    char c = tab[index];
    int ascii = c - 48;
    return ascii;
}

int str_to_int(char *tab, int len, int negative)
{
    long result = 0;
    for (int i = 1; i < len + 1; i++) {
        result += power10(len - i) * int_at(i - 1, tab);
    }
    if (negative) {
        result = -result;
    }
    if (len > 10) {
        return 0;
    }
    if (result > 2147483647 || result < -2147483648) {
        return 0;
    }
    return (int)result;

}

int my_getnbr(char const *str)
{
    int start = 0;
    int negative = 0;
    while ((str[start] < 48 || str[start] > 57) && str[start] != '\0')
        start++;
    if (my_strlen(str) == start)
        return 0;
    int end = start + 1;
    while (str[end] >= 48 && str[end] <= 57)
        end++;
    if (start != 0 && str[start - 1] == '-')
        negative = 1;
    char tab[end - start];
    int j = start;
    for (int i = 0; i < end - start; i++) {
        tab[i] = str[j];
        j++;
    }
    return str_to_int(tab, end - start, negative);
}
