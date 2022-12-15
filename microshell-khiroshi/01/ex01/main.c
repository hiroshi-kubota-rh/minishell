#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

// ls "|" head "|" wc

int main(int argc, char *argv[])
{
	int i = 1;
	int pipe_count = 0;
	int *pipe_place;
	pid_t pid;
	int status;

	//pipeの位置とか数とかを把握
	while (i < argc)
	{
		if (strcmp(argv[i], "|") == 0)
			pipe_count++;
		i++;
	}
	pipe_place = (int*)malloc((pipe_count + 1)* sizeof(int));
	i = 1;
	pipe_place[0] = 0;
	pipe_count = 0;
	while (i < argc)
	{
		if (strcmp(argv[i], "|") == 0)
		{
			argv[i] = NULL;
			pipe_count++;
			pipe_place[pipe_count] = i;
		}
		i++;
	}


	// pipeがないときの実装
	if (pipe_count == 0)
	{
		pid = fork();
		if ( pid == 0)
		{
			execvp(argv[1], &argv[1]);
			exit(0);
		}
		else if (pid > 0)
		{
			waitpid(pid, &status, 0);
			exit(WEXITSTATUS(status));
		}
		else
		{
			write(1 , "error\n", 6);
			exit(1);
		}
	}

	//pipeの実装
	i = 0;
	int pipefd[2];
	int tmppipefd[2];
	printf("pipe count %d \n", pipe_count);
	while (i < pipe_count + 1)
	{
		dprintf(2, "i = %d \n", i);
		if (i > 0)
		{
			tmppipefd[0] = pipefd[0];
			tmppipefd[1] = pipefd[1];
		}
		if (i < pipe_count)
		{
			pipe(pipefd);
		}
		pid = fork();
		if (pid == 0)
		{
			//最初のコマンドの時
			if (i == 0)
			{
				dup2(pipefd[1], 1);
				close(pipefd[1]);
				close(pipefd[0]);
			}
			else if (i == pipe_count)
			{
				dup2(tmppipefd[0], 0);
				close(tmppipefd[0]);
				close(tmppipefd[1]);
			}
			else
			{
				dup2(tmppipefd[0], 0);
				dup2(pipefd[1], 1);
				close(tmppipefd[0]);
				close(tmppipefd[1]);
				close(pipefd[0]);
				close(pipefd[1]);
			}
			execvp(argv[pipe_place[i] + 1], &argv[pipe_place[i] + 1]);
			exit(0);
		}
		else if (pid < 0)
		{
			write(1 , "error\n", 6);
			exit(1);
		}
		else
		{
			close(tmppipefd[0]);
			close(tmppipefd[1]);
		}
		i++;
	}

	i = 0;
	while(i < pipe_count + 1)
	{
		waitpid(pid, &status, 0);
		i++;
	}
}



//int main(void) {
//	int fd;
//	char *argv[3];
//	extern char **environ;
//
//	if ((fd = open("test.txt", O_WRONLY|O_CREAT|O_TRUNC, 0666)) < 0) {
//		perror("open");
//		return -1;
//	}
//
//	if (dup2(fd, 1) < 0) {
//		perror("dup2");
//		close(fd);
//		return -1;
//	}
//	close(fd);
//
//	/* echo を実行する */
//	argv[0] = "echo";
//	argv[1] = "Hello World!";
//	argv[2] = NULL;
//	execve("/bin/echo", argv, environ);
//
//	perror("execve");
//	return -1;
//}//
