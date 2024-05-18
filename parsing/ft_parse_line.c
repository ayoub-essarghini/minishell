#include "../parsing.h"

void ft_token(t_list *tab)
{
    while (tab)
    {
        if (ft_strlen(tab->input) > 1 && tab->input[0] == '$')
            tab->token = ENV;
        else if (ft_strcmp(tab->input, "|") == 0 && tab->status == 0)
            tab->token = PIPE_LINE;
        else if (ft_strcmp(tab->input, "<") == 0 && tab->status == 0)
            tab->token = REDIR_IN;
        else if (ft_strcmp(tab->input, ">") == 0 && tab->status == 0)
            tab->token = REDIR_OUT;
        else if (ft_strcmp(tab->input, ">>") == 0 && tab->status == 0)
            tab->token = REDIR_APPEND;
        else if (ft_strcmp(tab->input, "<<") == 0 && tab->status == 0)
            tab->token = HERE_DOC;
        else if (!all_space(tab->input) && tab->status == 0)
            tab->token = WHITE_SPACE;
        else if (!all_space(tab->input) && tab->status != 0)
            tab->token = QUOTES_SPACES;
        else
            tab->token = WORD;
        tab = tab->next;
    }
}

void check_env(t_list *tab, t_envs **envs)
{
    while (tab)
    {
        if (tab->token == ENV && tab->status != 1)
        {
            char *str = get_myenv(tab->input + 1, envs);
            if (str)
            {
                free(tab->input);
                tab->input = ft_strdup(str);
            }
            else
            {
                free(tab->input);
                tab->input = ft_strdup("");
                tab->token = NOT_DEF;
            }
        }
        tab = tab->next;
    }
}

void ft_parse_line(char *line, t_list **tab, t_list **last, t_envs **envs)
{
    ft_split_line(tab, line); // get the words from the line with the status
    ft_token(*tab);           // tokenization
    check_env(*tab, envs);    // // get the env if found otherwise we free the node
    ft_check_concate(tab, last);
    // print_nodes(*last);
    // check_parsing(last, root);
}