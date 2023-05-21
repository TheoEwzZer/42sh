/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** minishell
*/

#include "mysh.h"

bool is_separator(char c)
{
    return c == ' ' || c == '\n' || c == '\r' || c == '\t';
}

char **str_to_word_array2(char const *str, char **words,
    size_t num_words, int word_start)
{
    char *word = NULL;
    size_t len = strlen(str);
    size_t word_len = 0;

    if (word_start >= 0) {
        word_len = len - (size_t)word_start;
        word = calloc(word_len + 1, sizeof(char));
        strncpy(word, str + word_start, word_len);
        words[num_words++] = word;
    }
    words = realloc(words, sizeof(char *) * (num_words + 1));
    words[num_words] = NULL;
    return words;
}

char **str_to_word_array(char const *str)
{
    char **words = calloc(1, sizeof(char *));
    char *word = NULL;
    int word_start = -1;
    size_t len = strlen(str);
    size_t num_words = 0, word_len = 0;

    for (size_t i = 0; i < len; i++) {
        if (is_separator(str[i]) && word_start >= 0) {
            word_len = i - (size_t)word_start;
            word = calloc(word_len + 1, sizeof(char));
            strncpy(word, str + word_start, word_len);
            words[num_words++] = word;
            words = realloc(words,  sizeof(char *) * (num_words + 1));
            word_start = -1;
            continue;
        } if (word_start < 0 && !is_separator(str[i])) {
            word_start = (int)i;
        }
    }
    return str_to_word_array2(str, words, num_words, word_start);
}
