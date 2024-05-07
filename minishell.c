#include "parsing.h"

char *get_myenv(char *key, t_envs **envs)
{
    t_envs *tmp = *envs;
    char *value = NULL;
    while (tmp)
    {
        if (ft_strcmp(tmp->key, key) == 0)
        {
            value = ft_strdup(tmp->value);
        }
        tmp = tmp->next;
    }

    return (value);
}

void print_ascii()
{
    printf("\033[32m"); // Set color to green
    printf("#############################################################################################################\n");
    printf("#███╗   ███╗ █████╗ ██████╗ ███╗   ██╗███████╗███████╗███████╗      ███████╗██╗  ██╗███████╗██╗     ██╗     #\n");
    printf("#████╗ ████║██╔══██╗██╔══██╗████╗  ██║██╔════╝██╔════╝██╔════╝      ██╔════╝██║  ██║██╔════╝██║     ██║     #\n");
    printf("#██╔████╔██║███████║██║  ██║██╔██╗ ██║█████╗  ███████╗███████╗█████╗███████╗███████║█████╗  ██║     ██║     #\n");
    printf("#██║╚██╔╝██║██╔══██║██║  ██║██║╚██╗██║██╔══╝  ╚════██║╚════██║╚════╝╚════██║██╔══██║██╔══╝  ██║     ██║     #\n");
    printf("#██║ ╚═╝ ██║██║  ██║██████╔╝██║ ╚████║███████╗███████║███████║      ███████║██║  ██║███████╗███████╗███████╗#\n");
    printf("#╚═╝     ╚═╝╚═╝  ╚═╝╚═════╝ ╚═╝  ╚═══╝╚══════╝╚══════╝╚══════╝      ╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝#\n");
    printf("#############################################################################################################\n");
    printf("\033[0m");
}

void set_and_colorize_prompt(char cwd[1045], char **name, char *root, t_envs **envs)
{

    *name = strrchr(cwd, '/');

    root = get_myenv("HOME", &*envs);
    // printf("%s hhh\n",root);
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



void set_envs(char *envs[], t_envs **envs_lst)
{
    int i;
    char *key;
    char *value;

    i = 0;
    while (envs[i] != NULL)
    {
        key = get_key(envs[i]);
        value = get_value(envs[i]);
        creat_node(envs_lst, key, value);
        i++;
    }
}

char *get_mycwd(t_envs *env_list)
{
    t_envs *tmp = env_list;
    char *pwd;

    while (tmp)
    {
        if (ft_strcmp(tmp->key, "PWD") == 0)
            pwd = ft_strdup(tmp->value);
        tmp = tmp->next;
    }
    return (pwd);
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

    // print_ascii();
    // int i = 0;
    if (envs[0] == NULL)
        set_defautl_env(&env_list);
    else
        set_envs(envs, &env_list);
    tab = NULL;
    while (1)
    {
        if (getcwd(cwd, sizeof(cwd)) == NULL)
        {
            perror("getcwd");
            exit(EXIT_FAILURE);
        }
        set_and_colorize_prompt(cwd, &name, root, &env_list);
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
        free(cmd);
    }
}