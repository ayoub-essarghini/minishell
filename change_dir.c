#include "parsing.h"

void with_relative_path(t_list *cmds, t_envs **envs)
{
    if (chdir(cmds->next->input) == -1)
        perror("cd");
    char *old_pwd = get_myenv("PWD", &*envs);
    append_to_env(&*envs, "PWD", cmds->next->input);
    append_to_env(&*envs, "OLDPWD", old_pwd);
}

void with_absolute_path(t_list *cmds, t_envs **envs)
{
    char *root = get_myenv("PWD", &*envs);
    root = ft_strjoin(root, "/");
    root = ft_strjoin(root, cmds->next->input);

    if ((exist_env("PWD", &*envs) + exist_env("OLDPWD", &*envs)) == 0)
    {
        if (chdir(root) == -1)
            perror("cd");
        else
        {
            char *old_pwd2 = get_myenv("PWD", &*envs);
            char *value = ft_strjoin(old_pwd2, "/");
            value = ft_strjoin(value, cmds->next->input);
            append_to_env(&*envs, "PWD", value);
            append_to_env(&*envs, "OLDPWD", old_pwd2);
        }
    }
}

void change_directory(t_list *cmds, t_envs **envs)
{
    if (cmds->next != NULL)
    {
        if (cmds->next->input[0] == '/')
            with_relative_path(cmds, &*envs);
        else if (ft_strcmp(cmds->next->input, "-") == 0)
        {
            char *oldpwd = get_myenv("OLDPWD", &*envs);
            if (chdir(oldpwd) == -1)
                perror("cd");
            else
            {
                char *pwd = get_myenv("PWD", &*envs);
                append_to_env(&*envs, "PWD", oldpwd);
                append_to_env(&*envs, "OLDPWD", pwd);
            }
        }
        else if (ft_strcmp(cmds->next->input, "..") == 0)
        {
            
            if (chdir("..") == -1)
                perror("cd");
            else
            {
                char *pwd = get_myenv("PWD", &*envs);
                char *prevpwd = ft_strrchr(pwd,'/');
               
                // append_to_env(&*envs, "PWD", oldpwd);
                // append_to_env(&*envs, "OLDPWD", pwd);
            }
        }
        else
            with_absolute_path(cmds, &*envs);
    }

    else
    {
        if (chdir(".") == -1)
            perror("cd");
    }
}