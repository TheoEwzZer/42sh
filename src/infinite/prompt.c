/*
** EPITECH PROJECT, 2023
** prompt.c
** File description:
** prompt
*/
#include "mysh.h"

bool has_unpushed_changes(void)
{
    FILE *fp = NULL;
    char *line = NULL;
    const char *command = "git status --porcelain";
    int has_changes = false;
    size_t len = 0;

    fp = popen(command, "r");
    if (!fp)
        return false;
    while (getline(&line, &len, fp) != -1) {
        if (line[1] == 'M' || line[1] == 'A'
            || line[1] == 'D' || line[1] == 'R' || line[1] == '?') {
            has_changes = true;
            break;
        }
    }
    pclose(fp);
    free(line);
    return has_changes;
}

char *get_git_branch(void)
{
    FILE *fp = NULL;
    char *branch = NULL;
    char *line = NULL;
    const char *command = "git branch --show-current 2>/dev/null";
    size_t len = 0;

    fp = popen(command, "r");
    if (!fp)
        return NULL;
    if (getline(&line, &len, fp) != -1) {
        branch = strdup(line);
        branch[strlen(branch) - 1] = '\0';
    }
    free(line);
    pclose(fp);
    return branch;
}

char *current_dir(char *path)
{
    char *last_slash = strrchr(path, '/');

    if (!last_slash)
        return path;
    return last_slash + 1;
}

void write_prompt_with_branch(var_t *var, char *dir, char *branch)
{
    if (var->return_value == EXIT_SUCCESS)
        write(1, GREEN, 7);
    else
        write(1, RED, 7);
    write(1, "➜  ", 5);
    write(1, CYAN, 7);
    write(1, dir, strlen(dir));
    write(1, PURPLE, 7);
    write(1, " git:(", 6);
    write(1, RED, 7);
    write(1, branch, strlen(branch));
    write(1, PURPLE, 7);
    write(1, ") ", 2);
    if (has_unpushed_changes()) {
        write(1, YELLOW, 7);
        write(1, "✗ ", 4);
    }
    write(1, DEFAULT, 4);
}

void set_prompt(var_t *var)
{
    char *cwd = NULL;
    char *dir = NULL;
    char *branch = get_git_branch();

    cwd = getcwd(NULL, 0);
    if (cwd) {
        dir = current_dir(cwd);
        if (branch) {
            write_prompt_with_branch(var, dir, branch);
        } else {
            var->return_value == 0 ? write(1, GREEN, 7) : write(1, RED, 7);
            write(1, "➜  ", 5);
            write(1, CYAN, 7);
            write(1, dir, strlen(dir));
            write(1, " ", 1);
            write(1, DEFAULT, 4);
        }
    }
}
