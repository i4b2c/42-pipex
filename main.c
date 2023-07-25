#include "pipex.h"

//O QUE TEM QUE FAZER NO PIPEX ?
//./pipex file1 cmd1 cmd2 file2

//1 - escrever
//0 - ler

/*void exec_command(char *str)
{

}*/


int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (i < n && s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			break ;
		i++;
	}
	if (n == 0 || n == i)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

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


int ft_strlen(char *str)
{
	int i = 0;
	while(str[i] != 0)
		i++;
	return i;
}

// void split_path(char **path_split, char *path_simple)
// {

// }

char *getpath(char **str)
{
	int i = 0;
	char *path_simple;
	while(str[i] != NULL)
	{
		if(!(ft_strncmp("PATH=",str[i],5)))
		{
			path_simple = malloc(ft_strlen(str[i]));
			ft_strcpy_path(path_simple,str[i]);
		}
		i++;
	}
	return (path_simple);
	//split_path(path_split,path_simple);
	//printf("%s\n",path);
}

void print_all(char **str)
{
	int i = 0;
	while(str[i])
		printf("%s\n",str[i++]);
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

int main(int ac,char **av,char **envp)
{
	int fd[2];
	pid_t pid;
	int new_fd;
	char **path_split = malloc(sizeof(char *));
	char *path_simple = NULL;
	char **command;

	pipe(fd);
	if(ac != 5)
	{
		write(2,"Error\n",6);
		return -1;
	}
	path_simple = getpath(envp);
	path_split = ft_split(path_simple,':');
	char *check = NULL;
	pid = fork();
	if(pid == (pid_t) 0)
	{
		close(fd[0]);//fecha porque nao preciso ler
		new_fd = open("teste.txt", O_WRONLY | O_APPEND | O_CREAT , 0777);
		command = ft_split(av[2],' ');
		check = check_command(command[0],path_split);
		dup2(new_fd,1);
		if(check != NULL)
		{
			int a = 0;
			while(command[a] != NULL)
				a++;
			command[a] = malloc(256);
			ft_strcpy(command[a],av[1]);
			command[a+1] = NULL;
			execve(check,command,NULL);
		}
		else
			perror("Errro ");
		close(new_fd);
	}
	else if(pid < (pid_t) 0)
	{
		write(2,"Error\n",6);
		return -1;
	}
	else
	{
		wait(NULL);
		close(fd[1]);//fecha porque nao preciso escrever
		pid = fork();
		if(pid == 0)
		{
			new_fd = open("teste.txt",O_RDONLY);
			command = ft_split(av[3],' ');
			check = check_command(command[0],path_split);
			if(check != NULL)
			{
				int a = 0;
				while(command[a] != NULL)
					a++;
				command[a] = malloc(256);
				ft_strcpy(command[a],av[1]);
				command[a+1] = NULL;
				close(new_fd);
				new_fd = open(av[4], O_WRONLY | O_APPEND | O_CREAT , 0777);
				dup2(new_fd,1);
				execve(check,command,NULL);
			}
			else
				perror("Error ");
		}
		else
		{
			wait(NULL);
			unlink("teste.txt");//deleta o teste.txt
			printf("dinoguei lindo\n");
		}

	}
	return 0;
}
