/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** minishell
*/

#include "mysh.h"

void free_var(var_t *var)
{
    if (var->cwd)
        free(var->cwd);
    if (var->actu_path)
        free(var->actu_path);
    if (var->cmd)
        free(var->cmd);
    if (var->input)
        free(var->input);
    if (var->env && var->modify_env)
        free_env(var);
}

void free_env(var_t *var)
{
    for (size_t i = 0; var->env[i]; i++)
        free(var->env[i]);
    free(var->env);
}
