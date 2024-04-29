#include "parsing.h"

t_envs *ft_lstlast2(t_envs *lst)
{
    if (!lst)
        return (NULL);
    while (lst->next != NULL)
    {
        lst = lst->next;
    }
    return (lst);
}

int ft_lstsize2(t_envs *lst)
{
    t_envs *temp;
    int i;

    temp = lst;
    i = 0;
    while (temp != NULL)
    {
        temp = temp->next;
        i++;
    }
    return (i);
}






void ft_lstadd_back2(t_envs **lst, t_envs *new)
{
    t_envs *add;

    if (new)
    {
        if (!*lst)
        {
            *lst = new;
            new->next = NULL;
            return;
        }
        add = ft_lstlast(*lst);
        add->next = new;
        new->operator= 'c';
        new->next = NULL;
    }
}

t_envs *ft_lstnew2(char *key)
{
    t_envs *newnode;

    newnode = malloc(sizeof(t_envs));
    if (!newnode)
        return (NULL);
    newnode->key = strdup(key);
    newnode->next = NULL;
    newnode->operator= 'c';
    return (newnode);
}
char *ft_strjoin(char const *s1, char const *s2)

{
    char *new_str;
    int i;
    int j;

    if (!s1 && !s2)
        return (0);
    if (!s1)
        return (strdup(s2));
    if (!s2)
        return (strdup(s1));
    new_str = (char *)malloc(strlen(s1) + strlen(s2) + 1);
    if (!new_str)
        return (NULL);
    i = 0;
    while (s1[i] != '\0')
    {
        new_str[i] = s1[i];
        i++;
    }
    j = 0;
    while (s2[j] != '\0')
        new_str[i++] = s2[j++];
    new_str[i] = '\0';
    return (new_str);
}

void creat_node(t_envs **head, char *key)
{
    t_envs *new;

    if (*head == NULL)
    {
        *head = ft_lstnew2(key);
    }
    else
    {
        new = malloc(sizeof(t_envs));
        new->key = strdup(key);
        new->operator= 'c';
        new->next = NULL;
        ft_lstadd_back2(head, new);
    }
}
void execute_at_root()
{
    char *root = getenv("HOME");
    if (chdir(root) == -1)
    {
        perror("root file missed !");
        exit(EXIT_FAILURE);
    }
}

char *get_key(char *str)
{
    int len = 0;
    while (str[len] != '=')
        len++;
    char *new_str = (char *)malloc(sizeof(char) * len);

    strncpy(new_str, str, len);

    return new_str;
}

int unset_env(t_envs *envs, char *key)
{
    t_envs *tmp;

    tmp = envs;
    while (tmp)
    {
        char *k = get_key(tmp->key);
        if (strcmp(k, key) == 0)
        {
            free(tmp->key);
            free(tmp);
            return 0;
        }
        tmp = tmp->next;
    }
    return -1;
}

void handle_signal(int sig)
{
    if (sig == SIGINT)
    {
        printf("^C");
        rl_clear_signals();
    }
}
int main(int argc, char *argv[], char *env[])
{

    (void)argc;
    (void)argv;
    // (void)env;

    t_envs *envs;

    envs = NULL;

    int i = 0;

    while (env[i] != NULL)
    {
        creat_node(&envs, env[i]);
        i++;
    }

    // printf("%s\n",env[0]);

    execute_at_root();

    if (access("./test.txt", F_OK) == -1)
    {
        printf("permission denied !\n");
    }
    else
    {
        printf("access authorized ");
    }

    while (1)
    {
        // signal(SIGINT,handle_signal);
        char cwd[1045];
        if (getcwd(cwd, sizeof(cwd)) == NULL)
        {
            perror("getcwd");
            exit(EXIT_FAILURE);
        }
        char *name = strrchr(cwd, '/');
        char *root = getenv("HOME");
        root = strrchr(root, '/');
        if (strcmp(name + 1, root + 1) == 0)
        {

            name = ft_strjoin("", "\033[33m ➜\033[0m ");
        }
        else
        {
            name = ft_strjoin(" \033[33m", name + 1);
            name = ft_strjoin(name, "\33[0m\033[33m ➜\033[0m ");
        }
        char *cmd = readline(name);

        if (!cmd)
        {
            printf("\n");
            break;
        }
        add_history(cmd);
        if (strcmp(cmd, "exit") == 0)
        {
            printf("exit\n");
            exit(EXIT_SUCCESS);
        }

        pid_t pid = fork();

        if (pid == -1)
        {
            perror("fork error");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
            excute_cmd(cmd, envs);
        }
        else
        {
            wait(NULL);
        }
    }
    return (0);
}