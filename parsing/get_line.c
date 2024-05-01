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

void     double_quote(t_list **tab, char *line, int start, int i)
{
    char *word;

    if (line[i] == '"') 
    {
        // If closing double quote is found, extract the substring
        word = ft_word(line, start, i);
        creat_nodes(tab, word, 2);
        free(word);
    } 
    else 
    {
        // Handle error: Unclosed double quote
        printf("Error: Unclosed double quote\n");
        return; // Exit the function if the double quote is unclosed
    }
}

void single_quote(t_list **tab, char *line, int start, int i)
{
    char *word;

    if (line[i] == '\'') 
    {
        // If closing single quote is found, extract the substring
        word = ft_word(line, start, i);
        creat_nodes(tab, word, 1);
        free(word);
    } 
    else 
    {
        // Handle error: Unclosed single quote
        printf("Error: Unclosed single quote\n");
        return; // Exit the function if the single quote is unclosed
    }
}

void    word(t_list **tab, char *line, int start, int i)
{
        char *word;
        // Process normal word
        word = ft_word(line, start, i);
        creat_nodes(tab, word, 0);
            free(word);
}

void get_line(t_list **tab, char *line) 
{
    int i = 0;
    int start;
    
    while (line[i] == ' ' || line[i] == '\t') 
            i++;
    while (line[i] && line[i] != '\0') 
	{
        if (line[i] == '\'') 
		{
                // If double quote is encountered, find the closing double quote
            i++; // Move to the next character 
            start = i; // skip the opening double quote
            while (line[i] && line[i] != '\'') 
                i++; 
            single_quote(tab, line, start, i);
            i++;
        }
        else if (line[i] == '"') 
		{
            i++; // Move to the next character after the opening double quote
            start = i; // Update the start position to skip the opening double quote
            while (line[i] && line[i] != '"') 
                i++; 
            double_quote(tab, line, start, i);
            i++;
        }  
		else 
        {
            start = i;
            while (line[i] && line[i] != ' ' && line[i] != '\t' && line[i] != '\'' && line[i] != '"') 
                i++;
            word(tab, line, start, i);
        }
        while (line[i] == ' ' || line[i] == '\t') 
            i++;
    }
}
