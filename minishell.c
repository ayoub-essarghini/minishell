#include "parsing.h"
void set_and_colorize_prompt(char cwd[1045], char **name, char *root)
{

    *name = strrchr(cwd, '/');

    root = getenv("HOME");
    root = strrchr(root, '/');

    if (strcmp(*name + 1, root + 1) == 0)
    {

        *name = ft_strjoin("", "\033[33m ➜\033[0m ");
    }
    else
    {
        *name = ft_strjoin(" \033[33m", *name + 1);
        *name = ft_strjoin(*name, "\33[0m\033[33m ➜\033[0m ");
    }
}
char *get_value(char *str) {
    size_t i = 0;
    int j = 0;
    while (str[i] && str[i] != '=') {
        i++;
    }

    if (!str[i]) {
        fprintf(stderr, "No '=' found in the input string\n");
        exit(EXIT_FAILURE);
    }

    i++; // Move past the '=' delimiter
    j = 0;
    while (str[i + j]) {
        j++;
    }

    char *value = malloc((j + 1) * sizeof(char)); // Allocate memory for the value (+1 for the null terminator)
    if (value == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    strncpy(value, str + i, j); // Copy the value from the input string
    value[j] = '\0'; // Null-terminate the value string

    return value;
}
char *get_key(char *str) {
    size_t i = 0;
    while (str[i] && str[i] != '=') {
        i++;
    }

    char *key = malloc((i + 1) * sizeof(char)); // Allocate memory for the key (+1 for the null terminator)
    if (key == NULL) {
        // Memory allocation failed
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    strncpy(key, str, i); // Copy the key from the input string
    key[i] = '\0'; // Null-terminate the key string

    return key;
}

void set_envs(char *envs[], t_envs **envs_lst)
{
    int i;
    (void)envs_lst;
    i = 0;
    while (envs[i] != NULL)
    {
     char *key = get_key(envs[i]);
     char *value = get_value(envs[i]);
        // creat_node(envs_lst, envs[i]);
        printf("%s=",key);
        printf("%s\n",value);
        i++;
    }
}

int main(int argc, char *argv[], char *envs[])
{
    (void)argc;
    (void)argv;
    (void)envs;
    char cwd[1045];
    char *name = NULL;
    t_list *tab;
    t_envs *env_list = NULL;
    char *root = NULL;
    char *cmd = NULL;

    if (envs == NULL)
    {
        perror("env ");
        exit(0); }    
    // set_envs(envs,&env_list);
    // while (env_list != NULL)
    // {
    //   printf("%s\n",env_list->key);
    //   env_list = env_list->next;
    // }

    tab = NULL;
    while (1)
    {
        if (getcwd(cwd, sizeof(cwd)) == NULL)
        {
            perror("getcwd");
            exit(EXIT_FAILURE);
        }
        set_and_colorize_prompt(cwd, &name, root);
    
        cmd = readline(name);
        if (ft_strlen(cmd) > 0 && !check_line(cmd))
        {
            get_line(&tab, cmd);
            check_nodes(tab);
            // print_nodes(tab);
            check_first(tab, env_list);
            add_history(cmd);
            ft_free(tab);
            tab = NULL;
        }
        // free(cmd);
    }
}