#include "minishell.h"

static int get_eight_bit_num(char *s)
{
	int re;
	unsigned char c;

	re = atoi(s);
	c = (unsigned char)(re);
	return (c - '\0');
}

void	builtin_exit(int argc, char **argv)
{
	int	eight_bit_num;

	if (argc >= 3)
	{
		printf("bash: exit: too many arguments");
		exit(1);
	}
	if (argc == 1)
		exit (0);
	if (is_long(argv[1]) == false)
	{
		printf("bash: exit: %s: numeric argument required", argv[1]);
		exit(255);
	}
	else
	{
		eight_bit_num = get_eight_bit_num(argv[1]);
		exit(eight_bit_num);
	}
}