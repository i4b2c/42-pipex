#include "pipex.h"

void ft_strcpy_path(char *s1, char *s2)
{
	int i = 5;
	int j = 0;
	while(s2[i] != 0)
	{
		s1[j] = s2[i];
		i++;
		j++;
	}
}
char **getpath(char **str)
{
	int i = 0;
	char *path_simple;
	char **path;
	while(str[i] != NULL)
	{
		if(!(ft_strncmp("PATH=",str[i],5)))
		{
			path_simple = malloc(ft_strlen(str[i]));
			ft_strcpy_path(path_simple,str[i]);
		}
		i++;
	}
	path = NULL;
	path = ft_split(path_simple,':');
	free(path_simple);
	return (path);
}


char  *check_command(char *command, char **path)
{
	char *teste;
	int i = 0;

	while(path[i] != NULL)
	{
		teste = malloc(256);
		ft_strcpy(teste,path[i]);
		ft_strlcat(teste,"/",256);
		ft_strlcat(teste,command,256);
		if(access(teste,X_OK) == 0)
			return teste;
		i++;
		free(teste);
	}
	return NULL;
}
void error(void)
{
	write(2,"Error\n",6);
	exit(EXIT_FAILURE);
}

void exec(char *command, char **envp)
{
	char **path;
	char *check;
	char **cmd;

	cmd = ft_split(command,' ');
	path = getpath(envp);
	check = check_command(cmd[0],path);
	if(check != NULL)
		execve(check,cmd,envp);
	return ;
}

void child_process(char **av, char **envp,int fd[2])
{
	int file;

	file = open(av[1],O_RDONLY);
	if(file < 0)
		error();
	dup2(fd[1],STDOUT_FILENO);
	dup2(file,STDIN_FILENO);
	close(fd[0]);
	exec(av[2],envp);
	return ;
}

void parent_process(char **av, char **envp, int fd[2])
{
	int file;

	file = open(av[4],O_WRONLY | O_CREAT | O_TRUNC , 0777);
	if(file < 0)
		error();
	dup2(fd[0],STDIN_FILENO);
	dup2(file,STDOUT_FILENO);
	close(fd[1]);
	exec(av[3],envp);
	return ;
}

void pipex(char **av, char **envp)
{
	int fd[2];
	pid_t pid;

	pipe(fd);
	pid = fork();
	if(pid == 0)
		child_process(av,envp,fd);
	else
	{
		waitpid(pid,NULL,0);
		parent_process(av,envp,fd);
	}
	return ;
}

int main(int ac, char **av, char **envp)
{
	if(ac != 5)
		error();
	pipex(av,envp);
	return 0;
}
