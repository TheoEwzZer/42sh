/*
** EPITECH PROJECT, 2022
** 42sh.h
** File description:
** 42sh
*/

#ifndef MYSH_H_

    #define MYSH_H_

    #include "my.h"
    #include <ctype.h>
    #include <errno.h>
    #include <fcntl.h>
    #include <fcntl.h>
    #include <glob.h>
    #include <limits.h>
    #include <signal.h>
    #include <stdbool.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <sys/stat.h>
    #include <sys/types.h>
    #include <sys/types.h>
    #include <sys/wait.h>
    #include <time.h>
    #include <unistd.h>


    #define is_a_redirection(c) ((c) == '>' || (c) == '<' || (c) == '|')

    #define CYAN "\033[1;36m"
    #define DEFAULT "\033[0m"
    #define GREEN "\033[1;32m"
    #define PURPLE "\033[1;94m"
    #define RED "\033[1;31m"
    #define YELLOW "\033[1;33m"

typedef struct variables_s {
    char **value;
    char *variables;
    size_t argc;
    struct variables_s *next;
} variables_t;

typedef struct alias_s {
    char **command;
    char *alias;
    size_t argc;
    struct alias_s *next;
} alias_t;

typedef struct set_s {
    size_t i;
    size_t j;
} set_t;

typedef struct var {
    alias_t *alias;
    bool modify_env;
    bool redirect;
    char **env;
    char **history;
    char *actu_path;
    char *cmd;
    char *cwd;
    char *input;
    char *old_cmd;
    char *old_cwd;
    char *path;
    char *path_complete;
    char *term;
    char const *prompt;
    const char *home;
    int *history_hour;
    int *history_mins;
    int *pipe_descriptor;
    int fd;
    int return_value;
    int save_fd;
    pid_t pid;
    set_t *set;
    size_t *hist_count;
    size_t hist_save;
    size_t hist_value;
    size_t index;
    variables_t *variables;
} var_t;

bool check_backticks2(char **str2, size_t k, char *last);
bool check_builtin(char *str, var_t *var);
bool check_builtins_which(char *str);
bool check_command_not_found(char **str, var_t *var);
bool check_wrong_path(var_t *var, char **str);
bool contain_redirection(char **str);
bool contains_globbing(char *str);
bool error_where(char **str, var_t *var);
bool handle_error_scripting(char **str, var_t *var, FILE *file, size_t len);
bool has_unpushed_changes(void);
bool is_separator(char c);
bool is_valid_variable_value(const char *str);
bool isalphanum(char *str, size_t max);
bool where_slash(char *str, var_t *var);
bool write_str2(char **str, var_t *var, size_t *i, bool *line_break);
char **condition_inibitor(char **str, size_t i, size_t j);
char **condition_inibitor_bis(char **str, size_t i, size_t j);
char **create_str(var_t *var);
char **find_all_values(char **array);
char **get_alias(var_t *var, char *command, size_t *argc);
char **get_commands(var_t *var, char **commands);
char **get_variables(var_t *var, char *value, size_t *argc);
char **inibitors(char **str);
char **loop_echo(char **str, size_t j);
char **move_my_tab(char **str, size_t i);
char **my_str_to_word_delim(char *str, char delimiter);
char **my_strdup_double(char **src, char *env_to_set);
char **replace_cwd(char *new_cwd, var_t *var);
char **split_equals(char **input);
char **str_to_word_array(char const *str);
char **str_to_word_array2(char const *str, char **words,
    size_t num_words, int word_start);
char **strdup_double(char **src);
char *choose_command_history(var_t *var, char **str);
char *create_new_cwd(char *cwd);
char *create_new_env(char **str);
char *current_dir(char *path);
char *delete_exclamation(char *str, int nb);
char *get_git_branch(void);
char *move_my_str(char *str, size_t j);
char *my_strcat_malloc(char const *dest, char const *src);
char *my_strtok_r(char *str, const char *delim, char **saveptr);
char *split(char *input);
int check_good_number(char **str);
int handle_errors_set(char **str, var_t *var);
int handle_errors_setenv(char **str, var_t *var);
int my_char_isalpha(char c);
int starts_with_digit_and_has_alnum(char *str);
size_t get_index_input(char **str);
size_t get_index_output(char **str);
size_t get_index_pipe(char **str);
size_t nb_delim(char *str, char delim);
void add_alias(var_t *var, char *alias, char **command);
void add_variables(var_t *var, const char *variables, char **value);
void background_signals(char **str);
void begin_with_pipe(char **str, var_t *var);
void begin_with_redirection(char **str, var_t *var);
void builtin_alias(char **str, var_t *var);
void builtin_cd(char **str, var_t *var);
void builtin_echo(char **str, var_t *var);
void builtin_env(char **str, var_t *var);
void builtin_exit(char **str, var_t *var) __attribute__((noreturn));
void builtin_exit2(char **str, var_t *var) __attribute__((noreturn));
void builtin_foreach(char **str, var_t *var);
void builtin_history(var_t *var);
void builtin_redirection(char **str, var_t *var);
void builtin_set(char **str, var_t *var, bool first);
void builtin_set2(char **str, var_t *var, char *str2);
void builtin_setenv(char **str, var_t *var);
void builtin_unalias(char **str, var_t *var);
void builtin_unset(char **str, var_t *var);
void builtin_unsetenv(char **str, var_t *var);
void builtin_where(char **str, var_t *var);
void builtin_which(char **str, var_t *var);
void change_cwd(char **str, var_t *var);
void check(char **str, var_t *var);
void check_access(char *cmd, unsigned int *found);
void check_alias(var_t *var, char *alias);
void check_alias_where(var_t *var, char **str, size_t i, unsigned int *found);
void check_all_variable(char **str, var_t *var, size_t *i);
void check_all_variable2(variables_t *current_var, var_t *var);
void check_ambiguous_input_redirection(char **str, var_t *var);
void check_ambiguous_output_redirection(char **str, var_t *var);
void check_arg(int argc);
void check_backticks(char **str, var_t *var, size_t *i);
void check_builtins_where(char *str, unsigned int *found);
void check_error_output_redirection(char **str, var_t *var, bool *overwrite);
void check_not_found_and_close(char **str, var_t *var);
void check_variables(var_t *var, char *variables);
void check_where_commands(char **str, var_t *var, char **path, bool *not_found);
void choose_cmd(char **str, var_t *var);
void choose_cmd2(char **str, var_t *var);
void choose_cmd3(char **str, var_t *var);
void choose_cmd_4(char **str, var_t *var);
void choose_cmd_mouli(char **str, var_t *var);
void choose_cmd_mouli2(char **str, var_t *var);
void choose_cmd_mouli3(char **str, var_t *var);
void choose_cmd_mouli4(char **str, var_t *var);
void cmd_mouli(var_t *var);
void create_cmd(var_t *var, char **str);
void create_new_alias(var_t *var, char *alias, char **command);
void create_new_variables(var_t *var, const char *variables, char **value);
void create_variables(var_t *var);
void exec_script(char **str, var_t *var);
void execute_and_tokens(var_t *var, char *or_token, int *status);
void execute_commands(var_t *var);
void execute_first_command(char **str, var_t *var, int *status);
void execute_first_command_env(var_t *var);
void execute_first_command_where(char **str, var_t *var);
void execute_first_command_which(char **str, var_t *var);
void execute_or_tokens(var_t *var, char *semicolon_token);
void execute_repeat(var_t *var);
void execute_second_command(char **commands, var_t *var, pid_t pid2, int *stat);
void expand_alias(char ***str_ptr, char **command, size_t i, size_t argc);
void expand_variables(char ***str_ptr, char **value, size_t i, size_t argc);
void foreach_script(var_t *var, FILE *file, char **array);
void foreground_signals(char **str);
void found_home_and_path(var_t *var);
void found_special_variables(var_t *var);
void free_all(var_t *var);
void free_env(var_t *var);
void free_str_array(char **array);
void free_var(var_t *var);
void get_input(var_t *var);
void globbing(char **str, var_t *var) __attribute__((noreturn));
void handle_errors(int status, var_t *var);
void handle_errors_cd(char **str);
void handle_input_redirection(char **str, var_t *var);
void handle_output_redirection(char **str, var_t *var);
void handle_pipe(char **str, var_t *var);
void handle_pipe_env(char **str, var_t *var);
void handle_pipe_where(char **str, var_t *var);
void handle_pipe_which(char **str, var_t *var);
void handler(int signal);
void input_condition(int stock);
void malloc_history(var_t *var);
void number_condition(int c);
void parsing_path(var_t *var);
void print_alias(var_t *var);
void print_variables(var_t *var);
void redirection_input(char **str, var_t *var);
void redirection_output(char **str, var_t *var, bool overwrite);
void remove_alias(var_t *var, alias_t *prev_alias, alias_t *curr_alias);
void remove_env(char **str, size_t j, var_t *var);
void remove_variables(var_t *var, variables_t *prev_var, variables_t *curr_var);
void replace_foreach(var_t *var, char *variable, char *value);
void replace_with_alias(var_t *var, char ***str_ptr);
void replace_with_variables(var_t *var, char ***str_ptr);
void save_history(var_t *var);
void set_prompt(var_t *var);
void signal_handling(void);
void split2(char *input, size_t *i, size_t *j, char *new);
void try_path(char **str, var_t *var);
void try_path2(char **str);
void undefine_var(var_t *var, char **str, size_t i);
void update_alias(alias_t *alias, char **command);
void update_variables(variables_t *variables, char **value);
void wait_cmd(char **env, var_t *var);
void wait_cmd2(char **str, var_t *var);
void which_loop(char **str, var_t *var, char **alias, size_t i);
void write_cmd(char *cmd);
void write_prompt_with_branch(var_t *var, char *dir, char *branch);
void write_str(char **str, var_t *var, bool *line_break);
void write_token(char *token);
void write_token2(char *token, size_t i, size_t nbr);

#endif /* !MYSH_H_ */
