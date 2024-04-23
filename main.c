#include "minishell.h"

t_list *ft_lstlast(t_list *lst)
{
    if (!lst)
        return (NULL);
    while (lst->next != NULL)
    {
        lst = lst->next;
    }
    return (lst);
}

int ft_lstsize(t_list *lst)
{
    t_list *temp;
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

void ft_lstadd_back(t_list **lst, t_list *new)
{
    t_list *add;

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

t_list *ft_lstnew(char *key)
{
    t_list *newnode;

    newnode = malloc(sizeof(t_list));
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

void creat_nodes(t_list **head, char *key)
{
    t_list *new;

    if (*head == NULL)
    {
        *head = ft_lstnew(key);
    }
    else
    {
        new = malloc(sizeof(t_list));
        new->key = strdup(key);
        new->operator= 'c';
        new->next = NULL;
        ft_lstadd_back(head, new);
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

int unset_env(t_list *envs, char *key)
{
    t_list *tmp;

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
int excute_cmd(char *cmd, t_list *envs)
{

    if (strcmp(cmd, "ls") == 0)
    {
        // cmd[1] = NULL;
        char *args[] = {cmd, NULL};
        if (execve("/bin/ls", args, NULL) == -1)
        {
            printf("execution failed ");
            return (-1);
        }
    }
    else if (strcmp(cmd, "ls -la") == 0)
    {
        // cmd[1] = NULL;
        char *args[] = {cmd, "-la", NULL};
        if (execve("/bin/ls", args, NULL) == -1)
        {
            printf("execution failed ");
            return (-1);
        }
    }
    else if (strncmp(cmd, "echo", 4) == 0)
    {
        if (strlen(cmd) > 4)
        {

            if (*(cmd + 4) == ' ' && *(cmd + 5) == '-' && *(cmd + 6) == 'n' && *(cmd + 7) != '\0')
            {
                // printf("done");
                char *c = cmd + 8;
                printf("%s", c);
            }
            else
            {
                char *c = cmd + 5;
                printf("%s\n", c);
            }
        }
        else
        {
            printf("\n");
        }
    }
    else if (strncmp(cmd, "cd", 2) == 0)
    {
        if (*(cmd + 2) == '\0')
        {
            const char *home = getenv("HOME");
            if (chdir(home) == -1)
            {
                printf("Permission denied !");
            }
            // char cwd[1045];

            // if (getcwd(cwd,sizeof(cwd)) != NULL)
            // {
            //     printf("%s\n",cwd);
            // }
        }
        else
        {
            if (chdir(cmd + 3) == -1)
            {
                printf("Permission denied !");
            }
            //  char cwd[1045];
            // if (getcwd(cwd,sizeof(cwd)) != NULL)
            // {
            //     printf("%s\n",cwd);
            // }
        }
    }
    else if (strcmp(cmd, "env") == 0)
    {

        while (envs != NULL)
        {
            printf("%s\n", envs->key);
            envs = envs->next;
        }
    }
    else if (strncmp(cmd, "export", 6) == 0)
    {
        if (strcmp(cmd + 7, "\0") == 0)
        {
            while (envs != NULL)
            {
                printf("%s\n", envs->key);
                envs = envs->next;
            }
        }
        char *ocu;
        if ((ocu = strchr(cmd, '=')))
        {
            if (*(ocu + 1) != '\0')
            {
                creat_nodes(&envs, cmd + 7);
            }
        }
    }
    if (strncmp(cmd, "unset", 5) == 0)
    {
        if (*(cmd + 5) == '\0')
        {
            printf("unset : Not enough arguments!\n");
        }
        else
        {
            if (*(cmd + 6) != '\0')
            {

                // printf("%s", cmd + 6);

                if (unset_env(envs, cmd + 6) == 7)
                {
                    printf("unset %s successfully !", cmd + 6);
                }
            }
        }
    }

    return (0);
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

    t_list *envs;

    envs = NULL;

    int i = 0;

    while (env[i] != NULL)
    {
        creat_nodes(&envs, env[i]);
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