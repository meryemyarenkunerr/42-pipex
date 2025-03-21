#include "../includes/pipex.h"

void	child_process(char **argv, char **envp, int *fd)
{
	int	file_in;

	file_in = open(argv[1], O_RDONLY);
	if (file_in == -1)
		failure("File", argv[1]);
	dup2(fd[1], 1);
	dup2(file_in, 0);
	close(fd[0]);
	execute(argv[2], envp);
}

void	parent_process(char **argv, char **envp, int *fd)
{
	int	file_out;

	file_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (file_out == -1)
		failure("File", argv[4]);
	dup2(fd[0], 0);
	dup2(file_out, 1);
	close(fd[1]);
	execute(argv[3], envp);
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid1;

	if (argc == 5)
	{
		if (pipe(fd) == -1)
			failure("Pipe", "pipe");
		pid1 = fork();
		if (pid1 == -1)
			failure("Fork", "fork");
		if (pid1 == 0)
			child_process(argv, envp, fd);
		waitpid(pid1, NULL, 0);
		parent_process(argv, envp, fd);
	}
	else
		failure("Bad argument\n", " ");
	return (0);
}