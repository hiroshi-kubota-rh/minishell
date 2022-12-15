#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>






int main(int argc, char *argv[])
{
	pid_t pid;
	int status = 0;
	extern char **environ;

	pid = fork();
	if (pid > 0)
	{
		waitpid(pid, &status, 0); //waitpidはpidを返すが，これはエラー処理の対象になる場合があるので注意
		write(1, "parent process\n", 15);
		printf("status %d \n", WEXITSTATUS(status));
	}
	else if (pid == 0)
	{
		write(1, "child process\n", 14);
		execve(argv[1], &argv[1], environ);
		exit(0);
	}
	else
	{
		write(1, "error\n", 6);
	}
}
