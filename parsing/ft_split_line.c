#include "../parsing.h"

char	*ft_word(const char *str, int start, int end)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc(end - start + 1);
	if (!word)
		return (0);
	while (start < end)
	{
		word[i] = str[start];
		i++;
		start++;
	}
	word[i] = '\0';
	return (word);
}

void    ft_split_words(t_list **tab, const char *str, int status)
{
	int		i;
	int		start;
    char    *word;

	i = 0;
	start = 0;
	while (str[i])
	{
		if(str[i] == ' ' || str[i] == '\t')
        {
            start = i;
            while(str[i] == ' ' || str[i] == '\t')
                i++;
            word = ft_word(str, start, i);
            creat_nodes(tab, word, status);
            free(word);
        }
        else
        {
            start = i;
            while (str[i] != ' ' && str[i] != '\t' && str[i])
			    i++;
            word = ft_word(str, start, i);
            creat_nodes(tab, word, status);
            free(word);
        }
	}
}

void     double_quote(t_list **tab, char *line, int start, int i)
{
    char *word;

    if (line[i] == '"') 
    {
        word = ft_word(line, start, i);
        ft_split_words(tab, word, 2);
        free(word);
    } 
    else 
    {
        printf("Error: Unclosed double quote\n");
        return;
    }
}

void single_quote(t_list **tab, char *line, int start, int i)
{
    char *word;

    if (line[i] == '\'') 
    {
        word = ft_word(line, start, i);
        creat_nodes(tab, word, 1);
        //ft_split_words(tab, word, 1);
        free(word);
    } 
    else 
    {
        printf("Error: Unclosed single quote\n");
        return;
    }
}

void    word(t_list **tab, char *line, int start, int i)
{
        char *word;
        word = ft_word(line, start, i);
        creat_nodes(tab, word, 0);
            free(word);
}

void    ft_split_line(t_list **tab, char *line) 
{
    int i = 0;
    int start;
    
    while (line[i] == ' ' || line[i] == '\t') 
            i++;
    while (line[i] && line[i] != '\0') 
	{
        if (line[i] == '\'') 
		{
            i++;  
            start = i; 
            while (line[i] && line[i] != '\'') 
                i++; 
            single_quote(tab, line, start, i);
            i++;
        }
        else if (line[i] == '"') 
		{
            i++; 
            start = i; 
            while (line[i] && line[i] != '"') 
                i++; 
            double_quote(tab, line, start, i);
            i++;
        }  
		else if(line[i] == ' ' || line[i] == '\t')
        {
            start = i;
            while (line[i] == ' ' || line[i] == '\t') 
                i++;
            word(tab, line, start, i);
        }
        else if(line[i] == '$')
        {
            start = i;
            i++;
            while (line[i] && line[i] != ' ' && line[i] != '\t' && line[i] != '$') 
                i++;
            word(tab, line, start, i);
        }
        else if(line[i] == '|')
        {
            start = i;
            while (line[i] == '|') 
                i++;
            word(tab, line, start, i);
        }
        else if(line[i] == '<')
        {
            start = i;
            while (line[i] == '<') 
                i++;
            word(tab, line, start, i);

        }
        else if(line[i] == '>')
        {
            start = i;
            while (line[i] == '>') 
                i++;
            word(tab, line, start, i);
        }
        else 
        {
            start = i;
            while (line[i] && line[i] != ' ' && line[i] != '\t' && line[i] != '\'' && line[i] != '"' && line[i] != '$'
                            && line[i] != '|' && line[i] != '<' && line[i] != '>') 
                            i++;
            word(tab, line, start, i);
        }
    }
}