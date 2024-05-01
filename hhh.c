#include "stdio.h"
#include "string.h"
#include "stdlib.h"


int main()
{
    char *gg = "abcdefd";
    char *str = malloc(sizeof(char *) * (strlen(gg)+ 1));

    int i = 0;
    int j = 0;
    while (gg[i] != 'd' && gg[i])
        i++;
    while (i >= 0)
    {
        str[j] = gg[i];
       printf("%c",str[j]);
       i--;
       j++;
    }
    // while (gg[j])
    // {
    //     str[j] = gg[j];
    //     j++;
    // }
    // str[j] = '\0';
    //  printf("%s",str);
    
}