#include "minishell.h"

bool	is_long(char *s)
{
	long	result;
	long	minus;

	result = 0;
	minus = 1;
	if (*s == '+' || *s == '-')
	{
		if (strlen(s) == 1)
			return (false);
		if (*s++ == '-')
			minus = -1;
	}
	while ('0' <= *s && *s <= '9')
	{
		if (result > LONG_MAX / 10 && minus == 1)
			return (false);
		else if (result > LONG_MAX / 10 && minus == -1)
			return (false);
		else if (result == LONG_MAX / 10 && *s > '7' && minus == 1)
			return (false);
		else if (result == LONG_MAX / 10 && *s > '8' && minus == -1)
			return (false);
		result = ((*s++) - '0') + result * 10;
	}
	return (true);
}