/*
** EPITECH PROJECT, 2023
** signal.c
** File description:
** signal
*/
#include "mysh.h"

void handler(int signal)
{
    if (signal == SIGINT)
        return;
}

void foreground_signals(char **str)
{
    kill(atoi(str[1]), SIGTTOU);
    kill(atoi(str[1]), SIGTTIN);
    kill(atoi(str[1]), SIGCONT);
}

void background_signals(char **str)
{
    kill(atoi(str[1]), SIGTSTP);
}

void signal_handling(void)
{
    signal(SIGINT, handler);
    signal(SIGTSTP, handler);
}
