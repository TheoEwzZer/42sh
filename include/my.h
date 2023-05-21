/*
** EPITECH PROJECT, 2022
** my.h
** File description:
** my
*/

#include <stdarg.h>
#include <stddef.h>

#ifndef MY_H_

    #define MY_H_

char **my_str_to_word_array(char const *str);
char *increment_str1(int count, char *str_tmp);
char *increment_str2(int count, char *str_tmp, int *j);
char *my_revstr(char *str);
char *my_strcapitalize(char *str);
char *my_strcat(char *dest, const char *src);
char *my_strcpy(char *dest, char const *src);
char *my_strdup(char const *src);
char *my_strlowcase(char *str);
char *my_strncat(char *dest, char const *src, int nb);
char *my_strncpy(char *dest, char const *src, int n);
char *my_strstr(char *str, char const *to_find);
char *my_strupcase(char *str);
int check_end(int end, char *str_tmp);
int check_flags(char c);
int check_flags2(char c);
int check_isalpha(int i, char *str);
int check_word_actu(int word_actu, int *count);
int int_at(int index, char *tab);
int middle(char *str);
int my_char_is_space(char c);
int my_char_isnum(char str);
int my_compute_power_rec(int nb, int p);
int my_compute_square_root(int nb);
int my_compute_square_root2(int nb);
int my_find_prime_sup(int nb);
int my_getnbr(char const *str);
int my_is_prime(int nb);
int my_is_prime2(int nb);
int my_isneg(int n);
int my_put_nbr(long nbr, int count);
int my_put_nbr_count(long nbr, int count);
int my_put_ptr(unsigned int nbr, int count);
int my_putchar(char c);
int my_putfloat(double nb, int n);
int my_putfloat2(double decimal, int n, int count, double nb);
int my_putfloat3(double decimal, int n, int count, double nb);
int my_putnbr_base(unsigned int nbr, char *base, int count);
int my_putnbr_base_long(unsigned long nbr, char *base, int count);
int my_putstr(char const *str);
int my_showstr(char *str);
int my_str_isalpha(char *str);
int my_str_islower(char const *str);
int my_str_isnum(char const *str);
int my_str_isprintable(char const *str);
int my_str_isupper(char const *str);
int my_strcmp(char const *s1, char const *s2);
int my_strcmp_ignore_case(char const *s1, char const *s2);
int my_strncmp(const char *s1, const char *s2, size_t n);
int my_swapstr(char *a, char *b);
int str_to_int(char *tab, int len, int negative);
int word_count(const char *str);
int zero_before(char *array, int count);
int zero_before_zero(char *array, int count);
long power10(int len);
unsigned int my_strlen(char const *str);
unsigned int my_strlen_double(char *const *str);
void check_separator_lower(int i, char *str);
void check_separator_upper(int i, char *str);
void hexa(int i, char *str);
void my_show_word_array(char *const *tab);
void my_sort_int_array(int *array, int size);
void my_swap(int *a, int *b);
void my_swap_char(char **a, char **b);

#endif /* MY_H_ */
