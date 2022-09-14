# include "libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>

int main(void)
{
	int	pid;

	pid = fork();
	if (pid == 0)
		printf("ENFANT\n");
	else
		printf("PARENT\n");
	return (0);
}