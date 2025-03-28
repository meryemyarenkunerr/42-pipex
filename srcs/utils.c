#include "../includes/pipex.h"

void	failure(char *error, char *file_cmd)
{
	if (!ft_strncmp(error, "Pipe", 4))
		perror(file_cmd);
	else if (!ft_strncmp(error, "Fork", 4))
		perror(file_cmd);
	else if (!ft_strncmp(error, "File", 4))
		perror(file_cmd);
	else if (!ft_strncmp(error, "Path", 4))
	{
		ft_putstr_fd(file_cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
		free(file_cmd);
		exit(127);
	}
	else if (!ft_strncmp(error, "Exec", 4))
		perror(error);
	else
	{
		ft_putstr_fd(error, 2);
		ft_putstr_fd("Ex: ./pipex file1 cmd1 cmd2 file2\n", 2);
	}
	exit(EXIT_FAILURE);
}

void	ft_free_2(char **commands)
{
	int	i;

	i = -1;
	while (++i)
		free(commands[i]);
	free(commands);
}

char	*find_path(char *command, char **envp)
{
	char	**paths;
	char	*path_s;
	char	*abs_path;
	int		i;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = -1;
	while (paths[++i])
	{
		path_s = ft_strjoin(paths[i], "/");
		abs_path = ft_strjoin(path_s, command);
		free(path_s);
		if (access(abs_path, F_OK) == 0)
		{
			ft_free_2(paths);
			return (abs_path);
		}
		free(abs_path);
	}
	ft_free_2(paths);
	return (0);
}

void	execute(char *argv, char **envp)
{
	char	**commands;
	char	*path;
	char	*command;

	commands = ft_split(argv, ' ');
	command = ft_strdup(commands[0]);
	path = find_path(commands[0], envp);
	if (!path){
		ft_free_2(commands);
		failure("Path", command);
	}
	if (execve(path, commands, envp) == -1)
	{
		ft_free_2(commands);
		free(path);
		free(command);
		failure("Exec", "execve");
	}
}