#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include "../libft/libft.h"

void	failure(char *error, char *cmd);
void	execute(char *command, char **envp);
char	*find_path(char *command, char **envp);

#endif